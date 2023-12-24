from dataclasses import dataclass, field
from enum import Enum
import re
from typing import Any, Self

Signal = Enum("Signal", ["LOW", "HIGH"])

@dataclass
class Node:
    name: str = ""
    children: list[Self] = field(default_factory=list)

    def process(self, signal: Any) -> Any:
        return []

    def add_inbound(self, node: Self):
        return None

@dataclass
class SignalFire:
    src: Node
    dest: Node
    value: Signal

@dataclass
class BroadcasterNode(Node):
    def process(self, signal: SignalFire) -> list[SignalFire]:
        return [SignalFire(self, child, signal.value) for child in self.children]
    

@dataclass
class FlipFlopNode(Node):
    state: bool = False

    def process(self, signal: SignalFire) -> list[SignalFire]:
        if signal.value == Signal.LOW:
            self.state = not self.state
            if self.state == True:
                return [SignalFire(self, child, Signal.HIGH) for child in self.children]
            else:
                return [SignalFire(self, child, Signal.LOW) for child in self.children]
        return []

@dataclass
class ConjunctionNode(Node):
    state: dict[str, Signal] = field(default_factory=dict)
    
    def process(self, signal: Any) -> list[SignalFire]:
        self.state[signal.src.name] = signal.value
        if all(value == Signal.HIGH for value in self.state.values()):
            return [SignalFire(self, child, Signal.LOW) for child in self.children]
        else:
            return [SignalFire(self, child, Signal.HIGH) for child in self.children]
        
@dataclass
class State():
    nodes: dict[str, Node] = field(default_factory=dict)
    start: BroadcasterNode = field(default_factory=BroadcasterNode)

    def process_press(self) -> dict[Signal, int]:
        counts = {
            Signal.LOW: 0,
            Signal.HIGH: 0
        }
        queue = [SignalFire(Node("button"), self.start, Signal.LOW)]
        while len(queue) != 0:
            signal = queue.pop(0)
            counts[signal.value] += 1
            new_signals = signal.dest.process(signal)
            queue.extend(new_signals)
        return counts

    def calc_signal_sum(self, n: int):
        counts = {
            Signal.LOW: 0,
            Signal.HIGH: 0
        }
        for _ in range(0, n):
            round_counts = self.process_press()
            counts[Signal.LOW] += round_counts[Signal.LOW]
            counts[Signal.HIGH] += round_counts[Signal.HIGH]
        print(counts)
        return counts[Signal.LOW] * counts[Signal.HIGH]

def parse_line_for_nodes(state: State, line: str, _idx: int) -> State:
    if matches := re.match(r"^%([a-zA-Z]+)\s", line):
        state.nodes[matches.group(1)] = FlipFlopNode(matches.group(1))
    elif matches := re.match(r"^&([a-zA-Z]+)\s", line):
        state.nodes[matches.group(1)] = ConjunctionNode(matches.group(1))
    elif matches := re.match(r"^(broadcaster)\s", line):
        state.start = state.nodes[matches.group(1)] = BroadcasterNode(matches.group(1))
    else:
        raise Exception(f"Could not parse line: {line}")
    return state

def parse_line_for_edges(state: State, line: str, _idx: int) -> State:
    if matches := re.match(r"^[&%]?([a-zA-Z]+) -> (.*)$", line):
        children = matches.group(2).split(", ")
        for child in children:
            if child not in state.nodes:
                print(f"Weird node: {child}")
                state.nodes[child] = Node(child)
            state.nodes[child].add_inbound(state.nodes[matches.group(1)])
        state.nodes[matches.group(1)].children = [
            state.nodes[child] for child in children
        ]
    else:
        raise Exception(f"Could not parse line: {line}")
    return state


def process_file(state: State, filename: str, parse_functions: list):
    with open(filename) as file:
        for idx, line in enumerate(file):
            line = line.strip()
            for parse_func in parse_functions:
                state = parse_func(state, line, idx)
    return state

def calculate(filename):
    state = State()
    # Primera fase: Parsear nodos
    process_file(state, filename, [parse_line_for_nodes])
    # Segunda fase: Parsear conexiones (edges)
    process_file(state, filename, [parse_line_for_edges])
    return state.calc_signal_sum(1000)

print('Part 1', calculate("input.txt"))

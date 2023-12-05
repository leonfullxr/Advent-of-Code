#include <fstream>
#include <iostream> 
#include <numeric> 
#include <unordered_map> 
#include <vector> 

int main(int argc, char *argv[]) {
  const std::string input = argc > 1 ? argv[1] : "input.txt";
  std::ifstream file(input); 
  std::string line; 
  std::vector<std::string> cur_path;
  cur_path.push_back("/");
  std::unordered_map<std::string, size_t> sizes; 

  // Since one cannot ls arbitrary directories, all `ls` calls have to be in the 
  // current directory. Thus ignore all ls calls. Assuming that each directory
  // is checked exactly once, ignore creating a directory structure. If we find 
  // a file, add its size to the entire hierarchy 
  while (getline(file, line)) { 
    switch (line[0]) { 
      case '$': 
        if (line[2] == 'c') { 
          std::string next_dir = line.substr(5, line.size() - 5); 
          switch (next_dir[0]) { 
            case '/': cur_path.resize(1); break;
            case '.': cur_path.pop_back(); break;
            default: cur_path.push_back(next_dir); break;
          }
        }
        break;
      case 'd': break; // Ignore directory lines
      default:
        size_t size = std::stoi(line.substr(0, line.find(" "))); 
        for (auto itr = cur_path.begin(); itr != cur_path.end(); itr++) { 
          std::string full_path = std::accumulate(cur_path.begin(), itr + 1, std::string{}); 
          sizes[full_path] += size; 
        }
        break;
      }
    }

    size_t sum = 0; 
    size_t min = sizes["/"]; 
    const size_t needed = 30000000 - (70000000 - sizes["/"]); 
    for (const auto &e : sizes) { 
      if (e.second < 100000) 
        sum += e.second; 
      if (e.second > needed) 
        min = std::min(min, e.second);
    } 
    std::cout << sum << std::endl; 
    std::cout << min << std::endl;
    return 0;
}

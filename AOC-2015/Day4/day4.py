from hashlib import md5

puzz_input = 'iwrupvqb'
n = 1
found_five, found_six = False, False

while found_six == False:
    input_hash = md5((puzz_input + str(n)).encode()).hexdigest()
    if found_five != True and input_hash[:5] == '00000':
        print ("5: "+str(n))
        found_five = True
    if input_hash[:6] == '000000':
        print ("6: "+str(n))
        found_six = True
    n += 1
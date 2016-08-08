ops = ['+', '-', '*', '//']
answers = {}

for i in range(4):
	for j in range(4):
		for k in range(4):
			string = '4 {} 4 {} 4 {} 4'.format(ops[i], ops[j], ops[k])
			answer = eval(string)
			string = string.replace('//', '/')
			answers[str(answer)] = string

numInputs = int(input(''))

for i in range(numInputs):
	key = input('')
	if key in answers:
		print(answers[key], ' = ', key)
	else:
		print('no solution')
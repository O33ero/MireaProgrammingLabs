

alphabet = ['а', 'б', 'в', 'г', 'д', 'е', 'ж', 'з', 'и', 'й', 'к', 'л', 'м', 'н', 'о', 'п', 'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ъ', 'ы', 'ь', 'э', 'ю', 'я']
alphabet_count = [0] * 32
sum = 0
sum_count = 0


d = int(input("Шаг: ")) # Каждую P букву считать
temp = d - 1

P = int(input("С какой буквы считать (первая буква = 0): ")) # С какой буквы считать

name_in = str(input("Имя исходного файла: "))
name = str(name_in) + '-result'+ '.txt'

file_in = open(name_in, 'r')
file_out = open('data.csv', 'a')
file_result = open(name, 'w')




for char in file_in.read():
	
	# Не русская буква
	if (ord(char) - 1072) < 0 or (ord(char) - 1072) > 31:
		continue

	# Сдвиг от начала на P букв
	if P > 0:
		P -= 1
		continue

	# Каждая d-ая буква
	if temp != (d-1):
			temp += 1
			continue

	alphabet_count[ord(char) - 1072] += 1
	file_result.write(str(char))
	sum += 1
	temp = 0


for i in range(0,len(alphabet)):

	print(alphabet[i], alphabet_count[i] , sep = ' = ', end = '\n')



for i in range(0,len(alphabet)-1):
	sum_count += alphabet_count[i]*(alphabet_count[i] - 1)

print(sum_count/(sum*(sum-1)))

file_out.write(str(name_in) + ';' + str(sum) +  ';' + str(d) + ';' + str(sum_count/(sum*(sum-1))) + '\n')



file_out.close()
file_result.close()
file_in.close()


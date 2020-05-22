alphabet = ['а', 'б', 'в', 'г', 'д', 'е', 'ж', 'з', 'и', 'й', 'к', 'л', 'м', 'н', 'о', 'п', 'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ъ', 'ы', 'ь', 'э', 'ю', 'я']




name_a = str(input("Имя первого файла: "))
name_b = str(input("Имя второго файла: "))

file_result = open('result.txt', 'w')



for d in range(0,32):

    file_a = open(name_a, 'r')
    file_b = open(name_b, 'r')

    alphabet_count_a = [0] * 32
    alphabet_count_b = [0] * 32
    sum_a = 0
    sum_b = 0
    sum_count = 0

    for char in file_a.read():
        alphabet_count_a[ord(char) - 1072] += 1
        sum_a += 1

    for char in file_b.read():
        alphabet_count_b[(ord(char) - 1072 + d) % 32] += 1
        sum_b += 1

    

    for i in range(0,32):
        sum_count += alphabet_count_a[i] * alphabet_count_b[i]

    M = sum_count/(sum_a * sum_b)

    print('D = ' + str(d) + ': ' + str(M))
    file_result.write('D = ' + str(d) + ': ' + str(M) + '\n')

    file_a.close()
    file_b.close()


file_result.close()
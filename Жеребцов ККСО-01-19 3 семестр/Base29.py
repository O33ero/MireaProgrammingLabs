import sys


alphabet = "13579ABCDEFGHJKLMNPQRSTUVWXYZ" #"123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz" - Base58

# Шифрование
def encry(file): 
    

    ## Открытие Файла ##
    f = open(file, 'r')
    

    ## Достаем текст из файла ##
    word = ""                   # Исходное слово
    for ch in f.read():     
        word = word + ch


    ## Переводим текст в десятичную запись ##
    sum = 0                     # Перевод слова в десятичную запись
    k = 0;                      # Коэффицент степени

    for i in reversed(range(len(word))):

        x = ord(word[i])        # Кодировка символа
        sum = sum + x * (2 ** (k * 8)) 
        k = k + 1           

    ## Переводим в base58 из десятичный записи
    ch = []                    # Массив кодировок символов base58 в обратном порядке
    while sum != 0:
        ch.append(sum % 29)
        sum = sum // 29


    ## Выводим символы base58 ##
    for i in reversed(range(len(ch))):
        print(alphabet[ch[i]], end = '')


    ## Закрытие файла ##
    f.close()

#Расширование
def decry(file):

    ## Открытие Файла ##
    f = open(file, 'r')


    ## Переводим текст в десятичную запись ##
    sum = 0                     # Перевод слова в десятичную запись
    k = 0                       # Остаток

    for ch in f.read():

        for i in range(len(alphabet)):
            if ch == alphabet[i]:
                k = i
                break

        sum = sum * 29 + k


    ## Переводим в нормальный вид из десятичный записи ##
    ch = []
    while sum != 0:
        ch.append(sum % 256)
        sum = sum // 256


    ## Выводим символы ##
    for i in reversed(range(len(ch))):
        print(chr(ch[i]), end = '')


    ## Закрытие файла ##
    f.close()


#   main

command, file = input().split()

if command == '-d':
    decry(file)
elif command == '-e':
    encry(file)
else:
    print("Error: Unknown command!")

print("\n")



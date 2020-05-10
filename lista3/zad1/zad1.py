from sys import argv
from zlib import crc32

SIZE = 128
FLAG = '01111110'
CRC_SIZE = 32


def getSuite(code):
    crc = "{0:b}".format(crc32(code.encode()))
    code += '0' * (CRC_SIZE - len(crc)) + crc

    answer = ''
    counter = 0

    for bit in code:
        answer += bit
        if bit == '1':
            counter += 1
            if counter == 5:
                answer += '0'
                counter = 0
        else:
            counter = 0

    return FLAG + answer + FLAG


def getCodeFromSuite(suite):
    answer = ''
    counter = 0

    for bit in suite:
        if bit == '1':
            answer += bit
            counter += 1
        else:
            if counter < 5:
                answer += bit
            counter = 0

    return answer


def checkCRC(suite):
    crc = "{0:b}".format(crc32(suite[:-CRC_SIZE].encode()))
    crc = '0' * (CRC_SIZE - len(crc)) + crc
    return crc == suite[-CRC_SIZE:]


def encode(binaryCode):
    answer = ''

    for code in [binaryCode[i: i + SIZE] for i in range(0, len(binaryCode), SIZE)]:
        answer += getSuite(code)

    return answer


def decode(binaryCode):
    answer = ''

    for suite in binaryCode.split(FLAG):
        if suite != '':
            code = getCodeFromSuite(suite)

            if checkCRC(code):
                answer += code[:-CRC_SIZE]
            else:
                print('Wrong crc code')
                exit(-1)

    return answer


def errorInfo():
    print('Give arguments:\n'
          '--encode fileToEncode fileToWriteAnswer\nor\n'
          '--decode fileToDecode fileToWriteAnswer\n')


def main():
    if len(argv) < 4:
        errorInfo()
        exit()

    with open(argv[2], 'r') as dataFile:
        with open(argv[3], 'w') as answerFile:
            if argv[1] == '--encode':
                answerFile.write(encode(dataFile.read()))
            elif argv[1] == '--decode':
                answerFile.write(decode(dataFile.read()))
            else:
                errorInfo()


if __name__ == '__main__':
    main()

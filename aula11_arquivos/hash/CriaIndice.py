import struct
import hashlib
import os

hashSize = 900001
fileName = "data/cep.dat"
indexName = "data/cep-hash.dat"
dataFormat = "72s72s72s72s2s8s2s"
#é a string de formato usada pela função struct para definir 
#a estrutura dos registros no arquivo de dados. Nesse caso, 
#cada registro tem vários campos com tamanhos fixos.

indexFormat = "8sLL"
#é a string de formato usada para definir a estrutura dos registros no arquivo de índice. 
#Cada registro do índice contém a chave, o número do registro correspondente e um ponteiro 
#para o próximo registro com a mesma chave.

keyColumnIndex = 5 #é o índice da coluna que contem a chave

dataStruct = struct.Struct(dataFormat)
indexStruct = struct.Struct(indexFormat)

#funcao h(key) calcula o valor hasg da chave usando o algoritmo SHA-1
#e retorna um valor inteiro entre 0 e 'hashSize-1'. Esse valor será usado para determinar 
#em qual compartimento da tabela hash o registro será armazenado.
def h(key):
    return int(hashlib.sha1(key).hexdigest(),16)%hashSize

#fi = open(indexName,"wb")
#emptyIndexRecord = indexStruct.pack(b"",0,0)
#for i in range(0,hashSize):
#    fi.write(emptyIndexRecord)
#fi.close()

with open(indexName,"wb") as fi:
    emptyIndexRecord = indexStruct.pack(b"",0,0)
    for i in range(0,hashSize):
        fi.write(emptyIndexRecord)

#abre os arquivos
f = open(fileName,"rb")
fi = open(indexName,"r+b")

#move o cursor do arquivo indice para o final, obtendo o tamanho atual do arquivo
fi.seek(0,os.SEEK_END)
fileIndexSize = fi.tell()

recordNumber = 0 #numero de registros processados
while True:
    line = f.read(dataStruct.size)
    if len(line) == 0: # EOF
        break
    record = dataStruct.unpack(line) #desempacota os dados da linha lida
    key = record[keyColumnIndex] #recebe o valor da chave do registro atual
    p = h(key) #calcula o valor hash da chave
    fi.seek(p*indexStruct.size,os.SEEK_SET)
    indexRecord = indexStruct.unpack(fi.read(indexStruct.size))
    fi.seek(p*indexStruct.size,os.SEEK_SET)
    if indexRecord[0][0] == b"\0":
        fi.write(indexStruct.pack(key,recordNumber,0))
    else:
        nextPointer = indexRecord[2]
        fi.write(indexStruct.pack(indexRecord[0],indexRecord[1],fileIndexSize))
        fi.seek(0,os.SEEK_END)
        fi.write(indexStruct.pack(key,recordNumber,nextPointer))
        fileIndexSize = fi.tell()
    recordNumber += 1
f.close()
fi.close()

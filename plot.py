import matplotlib.pyplot as plt
import csv

tamanhos = []
tempos1 = []
tempos2 = []

with open("tempos.csv", "r") as arq:
    ler = csv.reader(arq, delimiter='\t')
    next(ler) 
    for linha in ler:
        if len(linha) < 3:
            continue
        try:
            tamanhos.append(int(linha[0]))
            tempos1.append(float(linha[1]))
            tempos2.append(float(linha[2]))
        except ValueError:
            continue

largura = 0.3
indices = range(len(tamanhos))

plt.bar([i - largura / 2 for i in indices], tempos1, label="Programa 1", width=largura)
plt.bar([i + largura / 2 for i in indices], tempos2, label="Programa 2", width=largura)

for i, (t1, t2) in enumerate(zip(tempos1, tempos2)):
    plt.text(i - largura / 2, t1 + 0.1, f'{t1:.2f}', ha='center')
    plt.text(i + largura / 2, t2 + 0.1, f'{t2:.2f}', ha='center')

plt.xlabel("Tamanho")
plt.ylabel("Tempo (ms)")
plt.title("Desempenho dos programas")

plt.xticks(indices, tamanhos)
plt.yticks()
plt.grid(True)
plt.legend()

plt.show()


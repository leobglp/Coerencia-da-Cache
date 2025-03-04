
# Coerência da cache

Este projeto tem o objetivo de analisar o comportamento de dois códigos e como eles impactam no desempenho da cache


## Funcionalidades

É medido o tempo de execução de dois códigos:
- O primeiro acessa a matriz na forma matriz[i][j]
- O segundo na forma matriz[j][i]
Após os testes percebe-se uma diferença no desempenho com o primeiro programa sendo o mais eficiente.

## Conclusão

Essa diferença ocorre devido aos príncipios de lcoalidade da memória, com o primeiro programa acessando dados em endereços mais próximos. Já o segundo programa precisa pular grandes blocos de memória para encontrar o que foi requisitado.


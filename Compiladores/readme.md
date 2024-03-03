Essa pasta é de um compilador basico feito em C, com as seguintes especificações:
Estrutura principal:
Sintaxe: programa nome_programa ( )
 Bloco
– nome_programa: corresponde ao identificador que
determina o nome do programa
– Bloco: composto por declaração das variáveis (opcional) e
pela sequência de comandos (nessa ordem)
Sintaxe: /*
 declaração das variáveis
 sequência de comandos
*/
5
Componentes Básicos
● Declaração de variáveis:
Sintaxe: tipo -> lista_ids ;
– tipo define o tipo de dado da variável
● Usaremos os tipos: int, char e float
– lista_ids: 1 ou + identificadores de variáveis separados por vírgula
● Ex: int-> idade; float -> nota, z; char-> c, letra, s;
● Comando de seleção:
– Sintaxe: se condição entao
 comando ou bloco
 senao
 comando ou bloco
Obs: comando permite uma única instrução
OPCIONAL
(pode ter ou não)
6
Componentes Básicos
● Comentários:
Sintaxe: % texto_comentario %
● Comandos de repetição:
– Sintaxe: enquanto condição faca
 comando ou bloco
Sintaxe: repita
 comando ou bloco
 ate condição ;
● Comando de atribuição:
Sintaxe: id <- expressao ;
7
Componentes Básicos
● Condições:
– Permite apenas operadores relacionais
● Igual (=), diferente (<>), menor (<), maior (>), menor ou igual (<=),
maior ou igual (>=)
● Expressões:
– Permite operadores aritméticos
● Soma (+), subtração (-), multiplicação (*), divisão (/) e exponenciação
(^)
– Permite constantes compatíveis com os tipos definidos:
● char deve estar entre apóstrofo (ex: ‘A’)
● int deve estar entre 0 e 32767 (sinal “-” tratado como operador unário)
● float pode ser ponto fixo (ex: 5.3) ou notação científica (ex: 0.1E-2)
– Permite parênteses para priorizar operações

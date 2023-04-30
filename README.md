Aluno: Matheus Sebastian Alencar de Carvalho
GRR: 20220065

O trabalho foi dividido em 5 módulos. 
Lib_lista_chave: Essa biblioteca é responsável pela criação, inserção ordenada, destruição, impressão em um arquivo de destino e recebimento de uma lista de chaves(a partir de um livro cifra ou a partir de um arquivo de chaves). A impressão e recebimento da lista trata também as listas de posições de cada chave.
Lib_lista_posicao:  Essa biblioteca é responsável pela criação, inserção ordenada e destruição de uma lista de posições. 
Lib_trata_arquivo: Essa biblioteca é utilizada apenas no Beale.c, onde é feito o tratamento de arquivos passados. Se já existirem não serão editados.
Codifica: Essa biblioteca é responsável por codificar um caracater isolado e um arquivo inteiro.
Decodifica: Essa biblioteca é responsável por decodificar um caracater isolado e um arquivo inteiro.

O trabalho foi feito por meio da implementação de duas listas ligadas, uma para as chaves (caracteres) e outra para representar as posições de cada chave, que serão os códigos de cada chave encontrada.

A lista ligada de chaves apresenta um inteiro que representa o tamanho da lista de chaves, um ponteiro para o inicio dessa lista, um nodo que apresenta um caractere (a chave), um ponteiro para o próximo nodo e um ponteiro para o inicio de uma lista ligada de posições.

A lista ligada de posições apresenta um inteiro que representa o tamanho da lista de posições, um ponteiro para o inicio, um nodo que apresenta uma string (um inteiro representado por uma string) e um ponteiro para o próximo nodo.

Cada nodo da lista de chaves apresenta uma lista de posições dentro dele, e o tamanho da lista de posições representa a quantidade de códigos para aquela chave em específico.

O motivo da escolha pelas posições serem representadas em strings foi baseado no fato de que a disciplina da ênfase na utilização e manipulação de strings. Além disso, por meio de strings, a liberdade na representação nos textos codificados e decodificados fica muito maior, onde "-1" poderia facilmente ser trocar por "espaço", "-2" por "quebra de linha" e "-3" por "desconhecido", mas como os exemplos passados apresentam apenas valores inteiros, foi utilizado string com apenas representações de valores inteiros. Por conta da escolha da utilização de strings, foi necessário fazer mais conversões de inteiros para strings e mais alocações, já é necessário limitar o tamanho da string antes da recepção dos seus valores. Por conta disso, a quantidade de alocações é aumentanda baseado na quantidade de posições que o livro cifra de origem contiver, uma vez que se fosse utilizado apenas inteiros não seria necessário alocar memória para cada um desses valores.

Ambas listas apresentam inserção no inicio e inserção ordenada. A inserção ordenada de posições não é obrigatória, uma vez que as posições sempre serão maiores e adicionadas no inicio da lista de posições. Entretanto, na hora de receber a lista por meio de um arquivo chave, se fosse inserido apenas no inicio da lista as posições ficariam na ordem inversa (no caso crescente), o que não foi tratado pelo enunciado, mas presumi que a lista de chaves era pra sempre ser representada em ordem crescente e a lista de posições sempre em ordem decrescente. Como a implementação da inserção ordenada chama a inserção no inicio caso o valor seja maior que o primeiro, acredito que uma chamada de função a mais não seria problema para a eficiência do programa.


A parte da codificação é feita da seguinte maneira: É passado uma chave (caractere) e ela é verificada em três opções:
Se for um ' ', representa um espaço e será codificado como a string "-1";
Se for um '\n', representa uma quebra de linha e será codificado como a string "-2";
Se for um caracter maiúsculos, ou seja, entre os valores "A" e "Z" da tabela ASCII, a chave é convertida em minúscula somando-a 32.

A partir disso, se a chave passada não entrar em nenhum dos dois primeiros casos, ela será buscada na lista de chaves, por meio de uma busca sequencial iniciada pelo ponteiro do inicio da lista e vai até o ponteiro ser igual a NULL ou encontrar uma chave que representa a chave passada.
Se for encontrada uma chave que representa o caractere a ser codificado, caso o tamanho da lista de posições for maior que um, será escolhido um número "aleatoriamente" entre 0 e (tamanho-1) e esse valor será o nésimo termo da lista de posições. Caso contrário, a letra codificada será representada por "-3", já que ela não existe na lista de chaves. 


A parte da decodificação é feita da seguinte maneira: É passado uma string (caractere codificado) e ela é verificada em três opções:
Se for um "-1", representa um espaço e será decodificado como o caractere ' ';
Se for um "-2", representa uma quebra de linha e será decodificado como o caractere '\n';
Se for um "-3", representa um caractere desconhecido e será decodificado como o caractere '-';

Se a decodificação não entrou em nenhum desses casos, passará por todas as chaves e será verificado se a posição existe na lista da chave atual, caso exista a posição nessa chave, ela representará o caractere decodificado. Se após passar por todas as chaves ainda não encontrou o valor passado, significa que essa posição não existe na lista atual (Pode acontecer caso uma mensagem codificada tente ser decodificada por um arquivo de chaves que não apresente aquela posição) e será codificado como o carctere '-'.


A biblioteca de tratamento dos arquivos apresenta 5 funções:
Uma que verifica se o arquivo já existe, todos os arquivos que serão acessados para escrita passam por essa verificação, e, por segurança, o programa é finalizado e nada será feito, apenas a liberação de arquivos que foram abertos para teste.
Outra verifica se o arquivo não existe, se não existir e for necessário ler aquele arquivo inexistente o programa é encerrado com uma mensagem de erro.
Outra abre o arquivo para leitura 
Outra abre o arquivo para escrita
Outra verifica se foi passado mais de um arquivo válido igual, como dois -c ArquivoDeChaves e -c ArquivoDechave, será mostrado uma mensagem avisando e será considerado o último arquivo enviado. Se for passado algum arquivo que não será utilizado não será apresentada nenhuma mensagem de erro já que não causa nenhum problema.

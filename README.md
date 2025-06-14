# 🔐 Minha Cifra — Projeto de Criptografia Didática


obs: para vizualir bonito do vscode, utilize: Ctrl+Shift+V   , fica bem mais bacana! :-:\

Bem-vindo ao projeto de cifra didática desenvolvido em C!  
Essa ferramenta permite **criptografar e descriptografar** textos simples usando uma chave de até 4 bytes, com operações inspiradas em conceitos clássicos como substituição, permutação e XOR.

---

## 🚀 Como compilar

Certifique-se de ter o `make` instalado (a maioria dos sistemas Unix já vem com ele por padrão).

```bash
make
```

---

## ▶️ Como executar

Após compilar, execute o programa com:

```bash
./MyAES
```

---

## 📝 Como usar

1. **Informe o nome do arquivo de entrada** quando solicitado.  
   Um arquivo chamado `input.txt` já está incluso como exemplo. Você pode:
   - Escrever diretamente nele, ou
   - Criar seu próprio arquivo e informar o nome na execução.

2. **Digite uma chave de até 4 bytes**  
   Exemplos de chaves válidas: `1234`, `abcd`, `@!#$`

3. Escolha a operação desejada:
   - Digite `1` para **Criptografar**
   - Digite `2` para **Descriptografar**

4. O resultado será salvo no arquivo `result.txt`.

---

## 🔁 Como descriptografar um texto cifrado

Se você quiser descriptografar um texto gerado anteriormente, basta:

- Copiar o conteúdo de `result.txt`
- Colar no `input.txt`
- Rodar novamente o programa com a **mesma chave**

---

## ✅ Requisitos

- Compilador C (`gcc` ou similar)
- `make` instalado

---

## 📁 Estrutura do projeto

```
├── input.txt       # Arquivo de entrada
├── result.txt      # Arquivo de saída (criptografado ou decriptado)
├── MyAES.c         # Código-fonte principal
├── MyAES.h         # Cabeçalho com funções e definições
├── Makefile        # Script de build
```

---

Feito com 🧠, café ☕ e uns bons XORs 🔄.  
Curioso? Testa outras chaves e veja o **efeito avalanche** em ação!

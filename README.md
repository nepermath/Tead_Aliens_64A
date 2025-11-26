# TEAD Aliens 64A – Relógio com Jogos Embutidos

Projeto de relógio digital com jogos clássicos embarcados, baseado em microcontrolador Atmel programado em C++, com design eletrônico e PCB desenvolvidos no Altium Designer.

## 🕹️ Jogos disponíveis

- **TEAD Aliens**: estilo *Space Invaders*
- **Centopeia**: estilo clássico *Centipede*

## 🕒 Modos de exibição do relógio

- **Versão 1**: mostra **hora e minuto**
- **Versão 2**: mostra **hora, minuto e segundo**

## ⚙️ Funcionalidades do sistema

- Menu de configuração completo para:
  - Data e hora
  - Seleção do jogo
  - Boot configurável
- Interface visual baseada em display numérico (provavelmente com LED)
- Sistema embarcado com controle total via firmware C++

## 📁 Estrutura do projeto

```text
TEad_Aliens_64A/
├── README.md                       # Arquivo de descrição do projeto
├── _BMP/                           # Imagens da placa (fotos e referências)
│
├── _Eletronica/
│   └── Game_TEAD_Aliens_6A-2/      # Esquemático e layout da PCB (Altium Designer)
│
├── _programa/
│   └── c++/
│       └── Game_TEAD_Aliens_64A/   # Código-fonte em C++ para Atmel Studio
│
└── outros arquivos e diretórios relacionados
```

## 🔧 Desenvolvimento

- Linguagem principal: **C++ (Atmel Studio)**
- Plataforma alvo: **Microcontrolador Atmel AVR**
- Design eletrônico: **Altium Designer**

## 📦 Status

Projeto em desenvolvimento/teste. Funcional, com jogos integrados, menu de configuração, e suporte a duas versões de relógio.

## 🛠️ Autor

Desenvolvido por **Néper**  
Engenharia eletrônica, firmware, e design mecânico.

---

> Este projeto é parte de um sistema completo embarcado com foco em jogos retrô e funções de relógio — ideal para aplicações educacionais, kits eletrônicos e retrô gaming embutido em relógios customizados.

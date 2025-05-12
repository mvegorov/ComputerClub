# 🖥️ Computer Club

Симулятор ежедневной работы компьютерного клуба с обработкой событий и расчетом выручки.

[полное тз.docx](https://github.com/user-attachments/files/20094965/%2B%2B.1.docx)

## Возможности

- ✅ Обработка 4 типов событий:
  - Приход клиента
  - Занятие стола
  - Ожидание в очереди
  - Уход клиента
- 📊 Финансовая аналитика:
  - Расчет дневной выручки
  - Учет времени занятости столов
- 🔍 Валидация входных данных
- ❌ Генерация ошибок при нарушении правил

## 🛠️ Сборка и запуск

### Windows (MinGW)
```bash
git clone https://github.com/mvegorov/ComputerClub.git
cd ComputerClub
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
computer_club_app.exe ..\input.txt

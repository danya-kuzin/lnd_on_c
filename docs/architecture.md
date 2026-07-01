# Архитектура проекта

## Главная идея

Игровая логика не должна зависеть от интерфейса.

Текстовый ввод, будущий Raylib-интерфейс и будущий TCP-клиент должны
превращать действия игрока в единый внутренний формат команды.

```text
text input -> GameCommand -> game_apply_command()
Raylib     -> GameCommand -> game_apply_command()
TCP        -> GameCommand -> game_apply_command()

# 🐍 Snake Game

Простая игра "Змейка" на C++ с использованием библиотеки Raylib.

## Особенности
- Управление змейкой с помощью стрелок
- Три вида фруктов со сменой текстур
- Портальные стены (выход с противоположной стороны)
- Подсчёт очков
- Визуализация игрового поля

## Теоретическая часть

### Игровое поле и координатная система

Игровое поле разбито на сетку квадратных ячеек фиксированного размера. Координаты объектов (змейки и еды) хранятся в виде целочисленных пар (x, y), где (0,0) — левый верхний угол поля.

---

### Представление змейки и её движение

Змейка представлена как последовательность сегментов, хранящихся в двусторонней очереди (deque). Это позволяет эффективно добавлять новый сегмент в голову змейки и удалять хвост при движении.
Движение реализуется путём добавления нового сегмента в направлении движения и удаления последнего сегмента, если змейка не растёт.

---

### Управление направлением змейки

Направление движения задаётся вектором с компонентами по осям X и Y. Управление осуществляется с помощью клавиш стрелок. Для предотвращения мгновенного разворота змейки на 180 градусов реализована проверка, запрещающая смену направления на противоположное текущему.

---

### Генерация позиции еды

Позиция еды генерируется случайным образом в пределах игрового поля с учётом того, что еда не должна появляться в клетках, занятых змейкой. Для этого при генерации случайной позиции проверяется её отсутствие в теле змейки.

---

### Проверка столкновений

Игра проверяет столкновение головы змейки с её телом. При столкновении игра сбрасывается. Также реализована логика "телепортации" змейки с одного края поля на другой, создавая эффект бесконечного пространства.

---

### Обновление игры и управление временем

Для равномерного обновления состояния игры используется таймер, который позволяет обновлять положение змейки с фиксированным интервалом времени, обеспечивая стабильную скорость игры.

---

## Запуск проекта

Для запуска игры необходимо:

1. Установить библиотеку Raylib.
2. Скомпилировать проект с подключением Raylib.
3. Запустить исполняемый файл.

---


## 🧩 Связь классов

```mermaid
classDiagram
  class Snake{
    -deque<Vector2> body
    -Vector2 direction
    +Draw()
    +Update()
    +Reset()
  }
  class Food{
    -Vector2 position
    -vector<Texture2D> textures
    +Draw()
    +GenerateRandomPos()
  }
  class Game{
    -Snake snake
    -Food food
    +Update()
    +Draw()
    +Check()
  }
  Snake --> Game
  Food --> Game


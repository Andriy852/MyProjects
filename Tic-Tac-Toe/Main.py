from turtle import *
import random


class Figure:
    """Батьківський клас фігура"""
    def __init__(self, x, y, colour="black"):
        self._x = x
        self._y = y
        self._visible = False
        self._color = colour

    def draw(self, colour):
        raise NotImplementedError("Can't draw an object of the Father Figure class")

    def show(self):
        self._visible = True
        self.draw(self._color)

    def hide(self):
        if self._visible:
            self._visible = False
            self.draw(bgcolor())

    def set_coordinates(self, x, y):
        self._x = x
        self._y = y


class Tic(Figure):
    """Клас хрестика"""
    def __init__(self, x, y, length, colour="black"):
        super().__init__(x, y, colour)
        self._line_length = length

    def draw(self, colour):
        up()
        pencolor(colour)
        setposition(self._x, self._y)
        setheading(45)
        down()
        forward(self._line_length/2)
        back(self._line_length/2)
        setheading(-45)
        forward(self._line_length/2)
        up()
        back(self._line_length/2)
        down()
        back(self._line_length/2)
        up()
        forward(self._line_length/2)
        setheading(45)
        down()
        back(self._line_length/2)


class Toe(Figure):
    """Клас нулика"""
    def __init__(self, x, y, r, colour="black"):
        super().__init__(x, y, colour)
        self._r = r

    def draw(self, colour):
        pencolor(colour)
        up()
        setheading(0)
        setposition(self._x, self._y-self._r)
        down()
        circle(self._r)


class Square(Figure):
    """Клас квадрата для малювання поля"""
    def __init__(self, x, y, length, colour="black"):
        super().__init__(x, y, colour)
        self._length = length

    def draw(self, colour):
        up()
        setposition(self._x, self._y)
        setheading(90)
        down()
        forward(self._length)
        right(90)
        forward(self._length)
        right(90)
        forward(self._length)
        right(90)
        forward(self._length)
        setheading(90)

    @property
    def y(self):
        return self._y

    @property
    def length(self):
        return self._length

    @property
    def x(self):
        return self._x


class GameField(Figure):
    """Клас ігрового поля, який малюється квадратами"""
    def __init__(self, x, y, length, colour="black"):
        super().__init__(x, y, colour)
        self.grid = Square(x, y, length/3, colour)  # Квадрат для створення сітки

    def draw(self, colour):
        for i in range(3):
            self.grid.draw(colour)
            self.grid.set_coordinates(self.grid.x, self.grid.y + self.grid.length)
            self.grid.draw(colour)
            self.grid.set_coordinates(self.grid.x, self.grid.y + self.grid.length)
            self.grid.draw(colour)
            self.grid.set_coordinates(self.grid.x + self.grid.length, self.grid.y - 2 * self.grid.length)


class Game:
    """Клас гри"""
    def __init__(self, x, y, field_length, colour="black"):
        self._x = x
        self._y = y
        self._length = field_length
        self._colour = colour
        self._grid_length = self._length / 3
        self.tic = Tic(self._x, self._y, (self._grid_length ** 2 + self._grid_length ** 2) ** 0.5)
        self.toe = Toe(self._x, self._y, self._grid_length / 2)

    def start(self):
        field = GameField(self._x, self._y, self._length)
        speed(25)
        field.show()  # намалювали поле

    def play_game(self):
        move = "Tic"
        numbers = [i for i in range(1, 10)]
        speed(10)
        board = ["" for _ in range(9)]
        while numbers:
            grid_number = random.choice(numbers)
            numbers.remove(grid_number)
            if move == "Tic":
                game1.draw_figure(grid_number, game1.tic)
                move = "Toe"
                board[grid_number - 1] = "+"
            else:
                game1.draw_figure(grid_number, game1.toe)
                move = "Tic"
                board[grid_number - 1] = "o"
            if self._game_over_check(board):
                res = self._game_over_check(board)
                print(res)
                return "GAME OVER"
        print("TIE GAME")

    def _game_over_check(self, board):
        if board[0] == board[1] == board[2] == "o" or board[3] == board[4] == board[5] == "o" \
                or board[6] == board[7] == board[8] == "o" or board[0] == board[4] == board[8] == "o" \
                or board[2] == board[4] == board[6] == "o" or board[0] == board[3] == board[6] == "o" \
                or board[1] == board[4] == board[7] == "o" or board[2] == board[5] == board[8] == "o":
            return "TOE HAS WON"
        elif board[0] == board[1] == board[2] == "+" or board[3] == board[4] == board[5] == "+" \
                or board[6] == board[7] == board[8] == "+" or board[0] == board[4] == board[8] == "+" \
                or board[2] == board[4] == board[6] == "+" or board[0] == board[3] == board[6] == "+" \
                or board[1] == board[4] == board[7] == "+" or board[2] == board[5] == board[8] == "+":
            return "TIC HAS WON"
        else:
            return None


    def draw_figure(self, place, figure):
        match place:
            case 1:
                x = y = self._x + self._grid_length / 2
            case 2:
                x, y = self._x+self._grid_length/2, self._y+self._grid_length+self._grid_length/2
            case 3:
                x, y = self._x + self._grid_length / 2, self._y + 2 * self._grid_length + self._grid_length / 2
            case 4:
                x, y = self._x + self._length / 2, self._y + self._grid_length / 2
            case 5:
                x, y = self._x + self._length / 2, self._y + self._length / 2
            case 6:
                x, y = self._x + self._length / 2, self._y + self._length - self._grid_length / 2
            case 7:
                x, y = self._x + self._length - self._grid_length / 2, self._y + self._grid_length / 2
            case 8:
                x, y = self._x + self._length - self._grid_length / 2, self._y + self._length / 2
            case 9:
                x, y = self._x + self._length - self._grid_length / 2, self._y + self._length - self._grid_length / 2
            case _:
                return
        figure.set_coordinates(x, y)
        figure.show()


if __name__ == '__main__':
    game1 = Game(-100, -100, 270)
    game1.start()
    game1.play_game()
    mainloop()


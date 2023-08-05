class Vector:
    """Клас вектора"""
    def __init__(self, args: list):
        if isinstance(args, Vector): #Конструктор копіювання
            self._values = args._values
        else:
            self._values = args

    def __add__(self, other):
        """Оператор додавання для вектора"""
        if isinstance(other, SquareMatrix):# Додаємо вектор до кожного стовпця матриці
            if len(self) == other.dimension:
                return type(other)([[self[i] + other[i, j] for j in range(len(self))] for i in range(len(self))])
            else:
                raise ValueError("Can't add a matrix of this dimension")
        elif isinstance(other, Vector):
            if len(self) == len(other):
                return Vector([self[i] + other[i] for i in range(len(self))])
            else:
                raise ValueError("Can't add vector of this dimension")
        elif isinstance(other, int) or isinstance(other, float):
            return Vector([self[i]+other for i in range(len(self))])
        else: # Породження помилки у разі додавання невірного типу
            raise TypeError(f"Can't add {type(other)} type to a vector")

    def __iadd__(self, other):
        if isinstance(other,Vector):
            for i in range(len(self)):
                self[i]+=other[i]
        elif isinstance(other,float) or isinstance(other,int):
            for i in range(len(self)):
                self[i]+=other
        return self

    def __mul__(self, other):
        """Скалярний добуток векторів"""
        if len(self) == len(other):
            res = 0
            for i in range(len(self)):
                res += self[i]*other[i]
            return res
        else:
            raise ValueError("Can't implement dot product on vectors of different dimensions")

    def __getitem__(self, item):
        if item>=len(self._values):
            raise IndexError("The index is out of range")
        return self._values[item]

    def __eq__(self, other):
        if isinstance(other, int):
            return all([True if self[i]==other else False for i in range(len(self))])
        elif isinstance(other, Vector):
            return all([True if self[i]==other[i] else False for i in range(len(self))])
        else:
            return ValueError(f"Can't compare {type(other)} to {type(self)} type")

    def __setitem__(self, key, value):
        if key>=len(self._values):
            raise IndexError("The index is out of range")
        self._values[key]=value

    def __len__(self):
        return len(self._values)

    def __abs__(self):
        return sum(x * x for x in self._values) ** 0.5

    def mean(self):
        return sum(self._values) / len(self._values)

    def max_el(self):
        return max(self._values)

    def min_el(self):
        return min(self._values)

    def __str__(self):
        return "".join(["{}   ".format(value) for value in self._values])


class Vector2D(Vector):
    def __init__(self,args):
        if isinstance(args, Vector2D):
            self._values = args._values
        else:
            super().__init__(args)


class Vector3D(Vector):
    def __init__(self,args):
        if isinstance(args, Vector3D):
            self._values = args._values
        else:
            super().__init__(args)

if __name__=="__main__":
    from square_matrix import SquareMatrix
    v1 = Vector([1,5,7])
    v2 = Vector([1,2,3])
    # print(v1+v2)
    # matrix = SquareMatrix.keyboard_input(3)
    # print(v1+matrix)
    # print(v2+matrix)
    # print(v1+5)
    # print(v2+1.5)
    # print(v1)
    v3 = Vector([1, 5, 7])
    print(v1*v2)
    print(v3 == 0)
    print(v1==v2)
    print(v1==v3)


class MatrixOperationError(ArithmeticError):
    def __init__(self, message, param1, param2):
        self.message = message
        self.param1 = param1
        self.param2 = param2

    def __str__(self):
        return f"{self.message}.\n{type(self.param1)}:\n{self.param1}\n {type(self.param2)}:\n{self.param2}"
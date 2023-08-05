from tkinter import *
from Matrix2D import *
from Matrix3D import *
from GaussianMethod import *

class MatricesCalculator(Tk):
    """
    Class of the main project
    """
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.geometry("750x550")
        title_label = Label(self, text="Square matrices calculator", font=("Arial", 35))  # create a title
        title_label.pack(side=TOP, fill=BOTH)

        # one of these strings will be text in a label which asks for input
        self.dimension_question = "Enter the number of dimensions:"
        self.equation_question = "Enter the number of equations:"

        choice_container = Frame(self) # container which will have buttons to do specific calculation
        choice_container.pack(side=LEFT, fill=BOTH, padx=14, pady = 50)

        # question label
        choice_label = Label(choice_container, text="What do you want to calculate", font=("Arial", 20))
        choice_label.grid(row=0, column=0)

        # button to add matrices
        add_matrices_button = Button(choice_container, text="Add two matrices", width="27", height="3",
                                     command = lambda: self.create_widgets(self.dimension_question, "Addition"))
        add_matrices_button.grid(row=1, column=0)

        # button to multiply matrices
        prod_matrices_button = Button(choice_container, text="Multiply two matrices", width="27", height="3",
                                      command = lambda: self.create_widgets(self.dimension_question, "Product"))
        prod_matrices_button.grid(row=2, column=0)

        # button to find the inverse of a matrix
        inverse_button = Button(choice_container, text="Calculate inverse of the matrix", width="27", height="3",
                                command = lambda: self.create_widgets(self.dimension_question, "Inverse"))
        inverse_button.grid(row=3, column=0)

        # buttons to solve the equation
        equation_solver_button = Button(choice_container, text="Solve the equation", width="27", height="3"
                                        ,command = lambda: self.create_widgets(self.equation_question, "Equation"))
        equation_solver_button.grid(row=4, column=0)

        # container where all the input and output will be
        self.right_container = None

    def create_widgets(self, text, operation_type):
        """
        :param text: self.dimension_question or self.equation_question variable
        :param operation_type: type of operation to perform
        :return:
        """
        if self.right_container: # if we already have this frame, destroy it
            self.right_container.destroy()
        self.right_container = RightContainer(self, text, operation_type)
        self.right_container.pack(side=RIGHT, fill=BOTH, expand=TRUE)

class RightContainer(Frame):
    """
    Class of the container where all the input and output will be
    """
    def __init__(self, master, text, operation_type):
        """
        :param master: Frame, where RightContainer frame will be
        :param text: Question about dimension or the number of equations
        :param operation_type: type of operation to perform
        """
        super().__init__(master)
        self.operation_type = operation_type

        # container with the question about dimension(number of equations) and Entry block
        self.dimension_container = Frame(self, width=250, height=50)

        # label with the question("Enter the number of dimensions" or "Enter the number of equations")
        self.enter_label = Label(self.dimension_container)
        self.enter_label.place(relx=0.1)
        self.enter_label["text"] = text

        # Entry where the user will input the dimension
        self.enter_dim = Entry(self.dimension_container, width=5)
        self.enter_dim.place(relx=0.4, rely=0.45)
        self.enter_dim.focus()
        #bind entry to do a function every time the entry is changed
        self.enter_dim.bind("<KeyRelease>", self.change_matrix_frame)
        # button which will make do calculations
        self.calculate_button = Button(self, text="Calculate", width=5, height=2,
                                  command=self.calculate)
        self.calculate_button.place(relx=0.5, rely=0.40, anchor=CENTER)
        self.dimension_container.place(relx=0.5, rely=0.1, anchor=CENTER)

        self.input_frame = None # frame where the input matrix(matrices) or equations will be
        self.res_frame = None # frame where the result will be shown

    def calculate(self):
        """
        Main function which calculates the result
        :return: None
        """
        if self.operation_type != "Equation": # if we have to calculate product, addition or inverse
            matrix_frames = self.input_frame.winfo_children() # a list of matrix frames
            if self.operation_type == "Addition" or self.operation_type == "Product":
                # create SquareMatrices
                matrix_1 = self.create_matrix(matrix_frames[0])
                matrix_2 = self.create_matrix(matrix_frames[1])

                # calculate the result
                res = matrix_1*matrix_2 if self.operation_type == "Product" else matrix_1+matrix_2
                self.print_res(res) # print the result in the window

            elif self.operation_type == "Inverse":
                # create SquareMatrix
                matrix = self.create_matrix(matrix_frames[0])
                # create a solver, which will calculate the inverse using Gaussian method
                solver = GaussianMethod(matrix)
                res = solver.find_inverse() # calculate
                if type(res) == str:
                    res_label = Label(self, text = res, font = ("Arial", 25))
                    res_label.place(relx=0.5, rely=0.7, anchor=CENTER)
                else:
                    self.print_res(res) # print the result
        else:
            coeff_frames = self.input_frame.winfo_children() # list of frames of coefficients and entries
            matrix_data = list()
            vector_data = list()
            for coeff_frame in coeff_frames:
                if isinstance(coeff_frame.winfo_children()[0], Entry): # fill the matrix_data
                    matrix_data.append(float(coeff_frame.winfo_children()[0].get()))
                else: # fill the vector of right coefficients data
                    vector_data.append(float(coeff_frame.winfo_children()[1].get()))
            matrix_data = [matrix_data[i:i+self.dimension] for i in range(0, self.dimension**2, self.dimension)]
            matrix = Matrix2D(matrix_data) if self.dimension == 2 \
                else Matrix3D(matrix_data)
            vector = Vector2D(vector_data) if self.dimension==2 else Vector3D(vector_data)
            solver = GaussianMethod(matrix, vector)
            res = solver.solve()
            res_label = Label(self, text = f"Result is: {str(res)}", font = ("Arial", 25))
            res_label.place(relx=0.5, rely=0.65, anchor=CENTER)

    def print_res(self, res):
        """
        :param res: result of our calculations
        :return: None
        """
        if self.res_frame: # if there was already a calculation, destroy it
            self.res_frame.destroy()
        self.res_frame = Frame(self, width = 18, height=12)  # create a frame for the result
        self.res_frame.place(relx=0.5, rely=0.7, anchor=CENTER)
        for i in range(self.dimension): # print the result
            for j in range(self.dimension):
                el_output = Label(self.res_frame, width=6,height = 4, fg="black", text=str(res[i][j]),
                                  font = ("Arial", 15), borderwidth=2, relief="solid")
                el_output.grid(row=i, column=j)

    def create_matrix(self, matrix_frame: Frame):
        """
        :param matrix_frame: frame which has entries elements
        :return: SquareMatrix type
        """
        data = []
        elements = matrix_frame.winfo_children() # list of all the entries
        x,y = 0,self.dimension # variables needed to slice the elements list(for making 3*3 list)
        for i in range(self.dimension):
            # add one row
            data.append(list(map(lambda element: float(element.get()), elements[x:y])))
            x,y = x+self.dimension, y+self.dimension
        matrix = Matrix2D(data) if self.dimension == 2 else Matrix3D(data)
        return matrix

    def change_matrix_frame(self, event):
        """
        Function which shows new matrix frame, every time the new number of dimensions inputed
        """
        try:
            self.dimension = int(self.enter_dim.get())
        # if not the right input or the entry is empty, pass
        except AttributeError:
            pass
        except ValueError:
            pass
        else:
            if self.input_frame: # destroy the previous frame
                self.input_frame.destroy()
            # based on the operation, create a frame
            match self.operation_type:
                case "Addition":
                    self.input_frame = InputFrame(self, self.dimension, 2)
                case "Product":
                    self.input_frame = InputFrame(self, self.dimension, 2)
                case "Inverse":
                    self.input_frame = InputFrame(self, self.dimension, 1)
                case "Equation":
                    self.input_frame = InputFrame(self, self.dimension)
            self.input_frame.place(relx=0.5, rely=0.25, anchor=CENTER)


class InputFrame(Frame):
    """
    Input frame, where the person will enter equation or a matrix
    """
    def __init__(self, master, dimension, num_matrices=None):
        super().__init__(master)
        if num_matrices == 1: # create one matrix frame if we calculate the inverse
            self.matrix_frame = self.create_matrix_frame(dimension)
            self.matrix_frame.pack()
        elif num_matrices == 2: # create 2 matrix frames if we add or multiply
            matrix_frame_1 = self.create_matrix_frame(dimension)
            matrix_frame_2 = self.create_matrix_frame(dimension)
            matrix_frame_1.grid(row = 0, column = 0)
            matrix_frame_2.grid(row = 0, column=1)
        else: # create an equation frame
            k = 1
            for i in range(dimension):
                for j in range(dimension):
                    var_coeff = Frame(self, width=7)
                    el_input = Entry(var_coeff, width=5) # entry of the coefficient
                    el_input.insert(0, "0")
                    el_input.pack(side=LEFT)
                    var_name = Label(var_coeff, text="x"+str(k)+" +" if j!=dimension-1 else "x"+str(k)) # label of the variable
                    var_name.pack(side=RIGHT)
                    var_coeff.grid(row=i, column=j)
                    k = 1 if k == dimension else k+1
                right_side = Frame(self, width = 8) # right side of the equation
                equal_label = Label(right_side, text = "=") # = label
                right_input = Entry(right_side, width = 5) # entry of the right side of the equation
                right_input.insert(0, "0")
                equal_label.pack(side=LEFT)
                right_input.pack(side=RIGHT)
                right_side.grid(row=i, column=dimension)

    def create_matrix_frame(self, dimension):
        """
        :param dimension: dimension of a matrix
        :return: Frame()
        """
        matrix_frame = Frame(self, width=400, height=250, padx=10)
        for i in range(dimension):
            for j in range(dimension):
                el_input = Entry(matrix_frame, width=5, bg="white", fg="black")
                el_input.insert(0, "0")
                el_input.grid(row=i, column=j)
        return matrix_frame


calculator = MatricesCalculator()
calculator.mainloop()
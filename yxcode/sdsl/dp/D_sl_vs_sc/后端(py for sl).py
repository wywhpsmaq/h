import tkinter as tk
from tkinter import messagebox
import random

class Minesweeper:
    def __init__(self, master):
        self.master = master
        self.master.title("Minesweeper")
        self.rows = 9
        self.cols = 9
        self.mines = 10
        self.buttons = []
        self.mines_positions = []
        self.game_over = False
        
        self.create_board()
        self.place_mines()
        
    def create_board(self):
        for i in range(self.rows):
            row = []
            for j in range(self.cols):
                button = tk.Button(self.master, width=2, height=1)
                button.grid(row=i, column=j)
                button.bind('<Button-1>', lambda e, row=i, col=j: self.click(row, col))
                button.bind('<Button-3>', lambda e, row=i, col=j: self.flag(row, col))
                row.append(button)
            self.buttons.append(row)
            
    def place_mines(self):
        positions = [(i, j) for i in range(self.rows) for j in range(self.cols)]
        self.mines_positions = random.sample(positions, self.mines)
        
    def count_adjacent_mines(self, row, col):
        count = 0
        for i in range(max(0, row-1), min(self.rows, row+2)):
            for j in range(max(0, col-1), min(self.cols, col+2)):
                if (i, j) in self.mines_positions:
                    count += 1
        return count
    
    def click(self, row, col):
        if self.game_over:
            return
            
        button = self.buttons[row][col]
        if str(button['state']) == 'disabled':
            return
            
        if (row, col) in self.mines_positions:
            button.config(text="#", bg='red')
            self.game_over = True
            self.reveal_all()
            messagebox.showinfo("Game Over", "You hit a mine!")
            return
            
        mines = self.count_adjacent_mines(row, col)
        button.config(state='disabled', relief='sunken')
        
        if mines > 0:
            button.config(text=str(mines))
        else:
            for i in range(max(0, row-1), min(self.rows, row+2)):
                for j in range(max(0, col-1), min(self.cols, col+2)):
                    if (i != row or j != col) and str(self.buttons[i][j]['state']) != 'disabled':
                        self.click(i, j)
                        
    def flag(self, row, col):
        if self.game_over:
            return
            
        button = self.buttons[row][col]
        if str(button['state']) != 'disabled':
            if button.cget('text') == '*':
                button.config(text='')
            else:
                button.config(text='*')
                
    def reveal_all(self):
        for i in range(self.rows):
            for j in range(self.cols):
                if (i, j) in self.mines_positions:
                    self.buttons[i][j].config(text="#")

if __name__ == "__main__":
    root = tk.Tk()
    game = Minesweeper(root)
    root.mainloop()
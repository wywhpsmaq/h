import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.Random;

public class sl extends JFrame {
    private final int SIZE = 9;
    private final int MINES = 10;
    private JButton[][] buttons;
    private int[][] mines;
    private boolean[][] revealed;
    private boolean gameOver;

    public sl() {
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        initializeGame();
    }

    private void initializeGame() {
        buttons = new JButton[SIZE][SIZE];
        mines = new int[SIZE][SIZE];
        revealed = new boolean[SIZE][SIZE];
        gameOver = false;
        setLayout(new GridLayout(SIZE, SIZE));
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                buttons[i][j] = new JButton();
                buttons[i][j].setPreferredSize(new Dimension(40, 40));
                final int row = i;
                final int col = j;
                buttons[i][j].addMouseListener(new MouseAdapter() {
                    @Override
                    public void mouseClicked(MouseEvent e) {
                        if (!gameOver) {
                            if (e.getButton() == MouseEvent.BUTTON1) {
                                revealCell(row, col);
                            }
                        }
                    }
                });
                add(buttons[i][j]);
            }
        }
        placeMines();
        calculateNumbers();

        pack();
        setLocationRelativeTo(null);
    }

    private void placeMines() {
        Random random = new Random();
        int minesPlaced = 0;
        while (minesPlaced < MINES) {
            int row = random.nextInt(SIZE);
            int col = random.nextInt(SIZE);
            if (mines[row][col] != -1) {
                mines[row][col] = -1;
                minesPlaced++;
            }
        }
    }

    private void calculateNumbers() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (mines[i][j] != -1) {
                    mines[i][j] = countAdjacentMines(i, j);
                }
            }
        }
    }

    private int countAdjacentMines(int row, int col) {
        int count = 0;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int newRow = row + i;
                int newCol = col + j;
                if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE) {
                    if (mines[newRow][newCol] == -1) {
                        count++;
                    }
                }
            }
        }
        return count;
    }

    private void revealCell(int row, int col) {
        if (revealed[row][col]) return;
        revealed[row][col] = true;

        if (mines[row][col] == -1) {
            gameOver = true;
            revealAllMines();
        } else {
            if (mines[row][col] == 0) {
                buttons[row][col].setEnabled(false);
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        int newRow = row + i;
                        int newCol = col + j;
                        if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE) {
                            if (!revealed[newRow][newCol]) {
                                revealCell(newRow, newCol);
                            }
                        }
                    }
                }
            } else {
                buttons[row][col].setText(String.valueOf(mines[row][col]));
            }
        }
        
        checkWin();
    }

    private void revealAllMines() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (mines[i][j] == -1) {
                    buttons[i][j].setText("💣");
                }
            }
        }
    }

    private void checkWin() {
        int unrevealedCount = 0;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (!revealed[i][j] && mines[i][j] != -1) {
                    unrevealedCount++;
                }
            }
        }
        if (unrevealedCount == 0) {
            gameOver = true;
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            new sl().setVisible(true);
        });
    }
}
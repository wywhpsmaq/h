class MinesweeperGame {
    constructor() {
        this.size = 10;
        this.mineCount = 10;
        this.board = [];
        this.openedCells = 0;
        this.flaggedMines = 0;
        this.gameOver = false;
        this.isFirstClick = true;
        
        this.initElements();
        this.bindEvents();
        this.startGame();
    }
    
    initElements() {
        this.mineCountElement = document.getElementById('mine-count');
        this.openedCountElement = document.getElementById('opened-count');
        this.gameBoardElement = document.getElementById('game-board');
        this.restartButton = document.getElementById('restart-btn');
        this.startButton = document.getElementById('start-btn');
        this.sizeInput = document.getElementById('size-input');
        this.mineCountInput = document.getElementById('mine-count-input');
        this.gameMessageElement = document.getElementById('game-message');
    }
    
    bindEvents() {
        this.restartButton.addEventListener('click', () => this.startGame());
        this.startButton.addEventListener('click', () => this.startGame());
    }
    
    startGame() {
        this.size = parseInt(this.sizeInput.value);
        this.mineCount = parseInt(this.mineCountInput.value);
        
        // 确保地雷数量不超过格子数量
        if (this.mineCount >= this.size * this.size) {
            this.mineCount = Math.max(1, Math.floor(this.size * this.size * 0.1));
            this.mineCountInput.value = this.mineCount;
        }
        
        this.openedCells = 0;
        this.flaggedMines = 0;
        this.gameOver = false;
        this.isFirstClick = true;
        this.gameMessageElement.textContent = '';
        this.gameMessageElement.className = '';
        
        this.initBoard();
        this.renderBoard();
        this.updateGameInfo();
    }
    
    initBoard() {
        // 初始化棋盘
        this.board = Array(this.size).fill().map(() => 
            Array(this.size).fill().map(() => ({ 
                isMine: false, 
                isOpened: false, 
                isFlagged: false, 
                adjacentMines: 0 
            }))
        );
    }
    
    generateMines(firstClickX, firstClickY) {
        let minesPlaced = 0;
        
        while (minesPlaced < this.mineCount) {
            const x = Math.floor(Math.random() * this.size);
            const y = Math.floor(Math.random() * this.size);
            
            // 确保不在第一次点击的位置及其周围放置地雷
            if ((Math.abs(x - firstClickX) > 1 || Math.abs(y - firstClickY) > 1) && !this.board[x][y].isMine) {
                this.board[x][y].isMine = true;
                minesPlaced++;
            }
        }
        
        // 计算每个格子周围的地雷数量
        this.calculateAdjacentMines();
    }
    
    calculateAdjacentMines() {
        for (let x = 0; x < this.size; x++) {
            for (let y = 0; y < this.size; y++) {
                if (!this.board[x][y].isMine) {
                    let count = 0;
                    for (let dx = -1; dx <= 1; dx++) {
                        for (let dy = -1; dy <= 1; dy++) {
                            const nx = x + dx;
                            const ny = y + dy;
                            if (this.isValid(nx, ny) && this.board[nx][ny].isMine) {
                                count++;
                            }
                        }
                    }
                    this.board[x][y].adjacentMines = count;
                }
            }
        }
    }
    
    isValid(x, y) {
        return x >= 0 && x < this.size && y >= 0 && y < this.size;
    }
    
    renderBoard() {
        this.gameBoardElement.innerHTML = '';
        
        for (let x = 0; x < this.size; x++) {
            const row = document.createElement('div');
            row.className = 'row';
            
            for (let y = 0; y < this.size; y++) {
                const cell = document.createElement('div');
                cell.className = 'cell';
                cell.dataset.x = x;
                cell.dataset.y = y;
                
                cell.addEventListener('click', (e) => this.handleCellClick(e, x, y));
                cell.addEventListener('contextmenu', (e) => this.handleCellRightClick(e, x, y));
                
                row.appendChild(cell);
            }
            
            this.gameBoardElement.appendChild(row);
        }
    }
    
    handleCellClick(event, x, y) {
        if (this.gameOver || this.board[x][y].isOpened || this.board[x][y].isFlagged) {
            return;
        }
        
        // 第一次点击时生成地雷，确保第一次点击不会踩雷
        if (this.isFirstClick) {
            this.generateMines(x, y);
            this.isFirstClick = false;
        }
        
        this.openCell(x, y);
        this.checkGameStatus();
    }
    
    handleCellRightClick(event, x, y) {
        event.preventDefault();
        if (this.gameOver || this.board[x][y].isOpened) {
            return;
        }
        
        this.toggleFlag(x, y);
    }
    
    openCell(x, y) {
        if (!this.isValid(x, y) || this.board[x][y].isOpened || this.board[x][y].isFlagged) {
            return;
        }
        
        this.board[x][y].isOpened = true;
        this.openedCells++;
        
        if (this.board[x][y].isMine) {
            this.gameOver = true;
            this.showAllMines();
            this.showGameMessage('游戏结束，你踩到了地雷！', 'lose');
            return;
        }
        
        // 如果是空白格子，递归打开周围的格子
        if (this.board[x][y].adjacentMines === 0) {
            for (let dx = -1; dx <= 1; dx++) {
                for (let dy = -1; dy <= 1; dy++) {
                    this.openCell(x + dx, y + dy);
                }
            }
        }
        
        this.updateCellDisplay(x, y);
        this.updateGameInfo();
    }
    
    toggleFlag(x, y) {
        this.board[x][y].isFlagged = !this.board[x][y].isFlagged;
        
        if (this.board[x][y].isFlagged) {
            if (this.board[x][y].isMine) {
                this.flaggedMines++;
            }
        } else {
            if (this.board[x][y].isMine) {
                this.flaggedMines--;
            }
        }
        
        this.updateCellDisplay(x, y);
        this.updateGameInfo();
        this.checkGameStatus();
    }
    
    updateCellDisplay(x, y) {
        const cellElement = this.gameBoardElement.querySelector(`[data-x="${x}"][data-y="${y}"]`);
        const cell = this.board[x][y];
        
        cellElement.className = 'cell';
        
        if (cell.isOpened) {
            cellElement.classList.add('opened');
            
            if (cell.isMine) {
                cellElement.classList.add('mine');
                cellElement.textContent = '💣';
            } else if (cell.adjacentMines > 0) {
                cellElement.classList.add(`number-${cell.adjacentMines}`);
                cellElement.textContent = cell.adjacentMines;
            }
        } else if (cell.isFlagged) {
            cellElement.classList.add('flagged');
            cellElement.textContent = '🚩';
        }
    }
    
    showAllMines() {
        for (let x = 0; x < this.size; x++) {
            for (let y = 0; y < this.size; y++) {
                if (this.board[x][y].isMine) {
                    this.board[x][y].isOpened = true;
                    this.updateCellDisplay(x, y);
                }
            }
        }
    }
    
    checkGameStatus() {
        // 检查是否胜利：所有非地雷格子都已打开
        if (this.openedCells === this.size * this.size - this.mineCount) {
            this.gameOver = true;
            this.showGameMessage('恭喜，你成功了！', 'win');
        }
        // 检查是否通过标记所有地雷胜利
        else if (this.flaggedMines === this.mineCount) {
            this.gameOver = true;
            this.showGameMessage('恭喜，你成功标记了所有地雷！', 'win');
        }
    }
    
    updateGameInfo() {
        this.mineCountElement.textContent = this.mineCount - this.flaggedMines;
        this.openedCountElement.textContent = this.openedCells;
    }
    
    showGameMessage(message, type) {
        this.gameMessageElement.textContent = message;
        this.gameMessageElement.className = type;
    }
}

// 页面加载完成后初始化游戏
document.addEventListener('DOMContentLoaded', () => {
    new MinesweeperGame();
});
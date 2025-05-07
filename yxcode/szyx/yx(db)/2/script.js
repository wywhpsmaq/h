// 游戏板大小
const BOARD_SIZE = 4;
// 游戏板
let board = [];
// 分数
let score = 0;
// 游戏是否结束
let gameOver = false;

// 初始化游戏板
function initBoard() {
    board = Array.from({ length: BOARD_SIZE }, () => Array(BOARD_SIZE).fill(0));
    score = 0;
    gameOver = false;
    document.getElementById('score').textContent = score;
    addRandomTile();
    addRandomTile();
    renderBoard();
}

// 在随机空位置添加一个新的数字（2 或 4）
function addRandomTile() {
    const emptyCells = [];
    for (let i = 0; i < BOARD_SIZE; i++) {
        for (let j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] === 0) {
                emptyCells.push({ x: i, y: j });
            }
        }
    }
    if (emptyCells.length > 0) {
        const randomCell = emptyCells[Math.floor(Math.random() * emptyCells.length)];
        board[randomCell.x][randomCell.y] = Math.random() < 0.9 ? 2 : 4;
    }
}

// 渲染游戏板
function renderBoard() {
    const gameBoard = document.getElementById('game-board');
    gameBoard.innerHTML = '';
    for (let i = 0; i < BOARD_SIZE; i++) {
        for (let j = 0; j < BOARD_SIZE; j++) {
            const cell = document.createElement('div');
            cell.classList.add('cell');
            if (board[i][j] !== 0) {
                cell.textContent = board[i][j];
                cell.style.backgroundColor = getTileColor(board[i][j]);
            }
            gameBoard.appendChild(cell);
        }
    }
}

// 根据数字获取瓷砖颜色
function getTileColor(value) {
    switch (value) {
        case 2: return '#eee4da';
        case 4: return '#ede0c8';
        case 8: return '#f2b179';
        case 16: return '#f59563';
        case 32: return '#f67c5f';
        case 64: return '#f65e3b';
        case 128: return '#edcf72';
        case 256: return '#edcc61';
        case 512: return '#edc850';
        case 1024: return '#edc53f';
        case 2048: return '#edc22e';
        default: return '#3c3a32';
    }
}

// 检查游戏是否结束
function checkGameOver() {
    for (let i = 0; i < BOARD_SIZE; i++) {
        for (let j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] === 0) {
                return false;
            }
            if (i < BOARD_SIZE - 1 && board[i][j] === board[i + 1][j]) {
                return false;
            }
            if (j < BOARD_SIZE - 1 && board[i][j] === board[i][j + 1]) {
                return false;
            }
        }
    }
    return true;
}

// 处理移动
function move(direction) {
    if (gameOver) return;
    let moved = false;
    let newBoard = JSON.parse(JSON.stringify(board));

    if (direction === 'up') {
        for (let j = 0; j < BOARD_SIZE; j++) {
            let newColumn = [];
            for (let i = 0; i < BOARD_SIZE; i++) {
                if (newBoard[i][j] !== 0) {
                    newColumn.push(newBoard[i][j]);
                }
            }
            for (let k = 0; k < newColumn.length - 1; k++) {
                if (newColumn[k] === newColumn[k + 1]) {
                    newColumn[k] *= 2;
                    score += newColumn[k];
                    newColumn[k + 1] = 0;
                    moved = true;
                }
            }
            newColumn = newColumn.filter(num => num !== 0);
            while (newColumn.length < BOARD_SIZE) {
                newColumn.push(0);
            }
            for (let i = 0; i < BOARD_SIZE; i++) {
                if (newBoard[i][j] !== newColumn[i]) {
                    moved = true;
                }
                newBoard[i][j] = newColumn[i];
            }
        }
    } else if (direction === 'down') {
        for (let j = 0; j < BOARD_SIZE; j++) {
            let newColumn = [];
            for (let i = BOARD_SIZE - 1; i >= 0; i--) {
                if (newBoard[i][j] !== 0) {
                    newColumn.push(newBoard[i][j]);
                }
            }
            for (let k = 0; k < newColumn.length - 1; k++) {
                if (newColumn[k] === newColumn[k + 1]) {
                    newColumn[k] *= 2;
                    score += newColumn[k];
                    newColumn[k + 1] = 0;
                    moved = true;
                }
            }
            newColumn = newColumn.filter(num => num !== 0);
            while (newColumn.length < BOARD_SIZE) {
                newColumn.push(0);
            }
            newColumn.reverse();
            for (let i = 0; i < BOARD_SIZE; i++) {
                if (newBoard[i][j] !== newColumn[i]) {
                    moved = true;
                }
                newBoard[i][j] = newColumn[i];
            }
        }
    } else if (direction === 'left') {
        for (let i = 0; i < BOARD_SIZE; i++) {
            let newRow = [];
            for (let j = 0; j < BOARD_SIZE; j++) {
                if (newBoard[i][j] !== 0) {
                    newRow.push(newBoard[i][j]);
                }
            }
            for (let k = 0; k < newRow.length - 1; k++) {
                if (newRow[k] === newRow[k + 1]) {
                    newRow[k] *= 2;
                    score += newRow[k];
                    newRow[k + 1] = 0;
                    moved = true;
                }
            }
            newRow = newRow.filter(num => num !== 0);
            while (newRow.length < BOARD_SIZE) {
                newRow.push(0);
            }
            for (let j = 0; j < BOARD_SIZE; j++) {
                if (newBoard[i][j] !== newRow[j]) {
                    moved = true;
                }
                newBoard[i][j] = newRow[j];
            }
        }
    } else if (direction === 'right') {
        for (let i = 0; i < BOARD_SIZE; i++) {
            let newRow = [];
            for (let j = BOARD_SIZE - 1; j >= 0; j--) {
                if (newBoard[i][j] !== 0) {
                    newRow.push(newBoard[i][j]);
                }
            }
            for (let k = 0; k < newRow.length - 1; k++) {
                if (newRow[k] === newRow[k + 1]) {
                    newRow[k] *= 2;
                    score += newRow[k];
                    newRow[k + 1] = 0;
                    moved = true;
                }
            }
            newRow = newRow.filter(num => num !== 0);
            while (newRow.length < BOARD_SIZE) {
                newRow.push(0);
            }
            newRow.reverse();
            for (let j = 0; j < BOARD_SIZE; j++) {
                if (newBoard[i][j] !== newRow[j]) {
                    moved = true;
                }
                newBoard[i][j] = newRow[j];
            }
        }
    }

    if (moved) {
        board = newBoard;
        addRandomTile();
        document.getElementById('score').textContent = score;
        renderBoard();
        gameOver = checkGameOver();
        if (gameOver) {
            alert('Game Over! Your score is: ' + score);
        }
    }
}

// 监听键盘事件
document.addEventListener('keydown', function (event) {
    switch (event.key) {
        case 'ArrowUp':
            move('up');
            break;
        case 'ArrowDown':
            move('down');
            break;
        case 'ArrowLeft':
            move('left');
            break;
        case 'ArrowRight':
            move('right');
            break;
    }
});

let touchStart = { x: 0, y: 0 };
document.getElementById('game-board').addEventListener('touchstart', (e) => {
    touchStart.x = e.touches[0].clientX;
    touchStart.y = e.touches[0].clientY;
});

document.getElementById('game-board').addEventListener('touchmove', (e) => {
    if (!touchStart.x || !touchStart.y) return;
    
    const dx = e.touches[0].clientX - touchStart.x;
    const dy = e.touches[0].clientY - touchStart.y;
    
    if (Math.abs(dx) > Math.abs(dy)) {
        move(dx > 0 ? 'right' : 'left');
    } else {
        move(dy > 0 ? 'down' : 'up');
    }
    
    touchStart = { x: 0, y: 0 };
});

// 新增瓷砖移动动画
function renderBoard() {
    const gameBoard = document.getElementById('game-board');
    const cells = gameBoard.querySelectorAll('.cell');
    cells.forEach(cell => cell.classList.remove('move-right', 'move-left', 'move-up', 'move-down'));

    for (let i = 0; i < BOARD_SIZE; i++) {
        for (let j = 0; j < BOARD_SIZE; j++) {
            const cell = document.createElement('div');
            cell.classList.add('cell', `cell-${board[i][j]}`);
            if (board[i][j] !== 0) {
                cell.textContent = board[i][j];
                // 添加移动方向类
                if (prevBoard[i][j] !== board[i][j]) {
                    cell.classList.add(getMoveClass(i, j));
                }
            }
            gameBoard.appendChild(cell);
        }
    }
    prevBoard = JSON.parse(JSON.stringify(board));
}

// 计算移动方向
function getMoveClass(i, j) {
    if (prevBoard[i][j] === 0) return '';
    if (prevBoard[i][j] !== board[i][j]) {
        if (i < prevI[i][j]) return 'move-down';
        if (i > prevI[i][j]) return 'move-up';
        if (j < prevJ[i][j]) return 'move-right';
        if (j > prevJ[i][j]) return 'move-left';
    }
    return '';
}

// 初始化游戏
initBoard();
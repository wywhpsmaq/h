document.addEventListener('DOMContentLoaded', () => {
    const gameBoard = document.getElementById('game-board');
    const message = document.getElementById('message');
    let selectedCells = [];
    let boardSize = 4;
    let board = [];

    document.getElementById('easy').addEventListener('click', () => startGame(4));
    document.getElementById('medium').addEventListener('click', () => startGame(6));
    document.getElementById('hard').addEventListener('click', () => startGame(10));

    function startGame(size) {
        boardSize = size;
        board = generateBoard(size);
        renderBoard();
        message.textContent = '';
    }

    function generateBoard(size) {
        const board = [];
        for (let i = 0; i < size * size; i++) {
            board.push(Math.floor(Math.random() * 98) + 3); // 生成3~100的随机数
        }
        return board;
    }

    function renderBoard() {
        gameBoard.innerHTML = '';
        gameBoard.style.gridTemplateColumns = `repeat(${boardSize}, 60px)`;
        board.forEach((num, index) => {
            const cell = document.createElement('div');
            cell.textContent = num;
            cell.addEventListener('click', () => selectCell(index));
            gameBoard.appendChild(cell);
        });
    }

    function selectCell(index) {
        if (selectedCells.length < 2 && !selectedCells.includes(index)) {
            selectedCells.push(index);
            gameBoard.children[index].style.backgroundColor = '#FFA500';
            if (selectedCells.length === 2) {
                processSelection();
            }
        }
    }

    function processSelection() {
        const [index1, index2] = selectedCells;
        const num1 = board[index1];
        const num2 = board[index2];
        const gcdValue = gcd(num1, num2);

        if (gcdValue > 1) {
            board[index1] = num1 / gcdValue;
            board[index2] = num2 / gcdValue;
            if (board[index1] === 1) board[index1] = 0;
            if (board[index2] === 1) board[index2] = 0;
            renderBoard();
            checkGameStatus();
        } else {
            message.textContent = '无法消除，请重新选择';
        }
        selectedCells = [];
    }

    function gcd(a, b) {
        if (b === 0) return a;
        return gcd(b, a % b);
    }

    function checkGameStatus() {
        if (board.every(num => num === 0)) {
            message.textContent = '恭喜你，游戏成功！';
        } else if (board.filter(num => num !== 0).length < 2) {
            message.textContent = '游戏失败，无法继续消除';
        }
    }
});
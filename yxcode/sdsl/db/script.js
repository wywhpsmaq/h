let gameBoard;
let width, height, depth, mines;
let gameOver = false;

// Three.js 相关变量
let scene, camera, renderer;
let cubes = [];
let controls;

function startGame(w, h, d, m) {
    width = w;
    height = h;
    depth = d;
    mines = m;
    initializeGame();
    setupThreeJS();
}

function customStartGame() {
    width = parseInt(document.getElementById('customWidth').value);
    height = parseInt(document.getElementById('customHeight').value);
    depth = parseInt(document.getElementById('customDepth').value);
    mines = parseInt(document.getElementById('customMines').value);
    initializeGame();
    setupThreeJS();
}

function initializeGame() {
    gameOver = false;
    gameBoard = [];
    for (let z = 0; z < depth; z++) {
        gameBoard[z] = [];
        for (let y = 0; y < height; y++) {
            gameBoard[z][y] = [];
            for (let x = 0; x < width; x++) {
                gameBoard[z][y][x] = {
                    hasMine: false,
                    revealed: false,
                    flagged: false,
                    minesAround: 0
                };
            }
        }
    }
    placeMines();
    calculateMinesAround();
}

function placeMines() {
    let placedMines = 0;
    while (placedMines < mines) {
        let x = Math.floor(Math.random() * width);
        let y = Math.floor(Math.random() * height);
        let z = Math.floor(Math.random() * depth);
        if (!gameBoard[z][y][x].hasMine) {
            gameBoard[z][y][x].hasMine = true;
            placedMines++;
        }
    }
}

function calculateMinesAround() {
    for (let z = 0; z < depth; z++) {
        for (let y = 0; y < height; y++) {
            for (let x = 0; x < width; x++) {
                if (!gameBoard[z][y][x].hasMine) {
                    let count = 0;
                    for (let dz = -1; dz <= 1; dz++) {
                        for (let dy = -1; dy <= 1; dy++) {
                            for (let dx = -1; dx <= 1; dx++) {
                                if (dz === 0 && dy === 0 && dx === 0) continue;
                                let newZ = z + dz;
                                let newY = y + dy;
                                let newX = x + dx;
                                if (newZ >= 0 && newZ < depth && newY >= 0 && newY < height && newX >= 0 && newX < width) {
                                    if (gameBoard[newZ][newY][newX].hasMine) {
                                        count++;
                                    }
                                }
                            }
                        }
                    }
                    gameBoard[z][y][x].minesAround = count;
                }
            }
        }
    }
}

function setupThreeJS() {
    // 创建场景
    scene = new THREE.Scene();

    // 创建相机
    camera = new THREE.PerspectiveCamera(75, 800 / 600, 0.1, 1000);
    camera.position.z = 20;

    // 创建渲染器
    renderer = new THREE.WebGLRenderer();
    renderer.setSize(800, 600);
    document.getElementById('three-container').appendChild(renderer.domElement);

    // 创建网格
    const geometry = new THREE.BoxGeometry(1, 1, 1);
    const material = new THREE.MeshBasicMaterial({ color: 0x00ff00 });

    cubes = [];
    for (let z = 0; z < depth; z++) {
        cubes[z] = [];
        for (let y = 0; y < height; y++) {
            cubes[z][y] = [];
            for (let x = 0; x < width; x++) {
                const cube = new THREE.Mesh(geometry, material);
                cube.position.set(x - width / 2, y - height / 2, z - depth / 2);
                scene.add(cube);
                cubes[z][y][x] = cube;

                // 添加点击事件
                cube.userData = { x, y, z };
                cube.addEventListener('click', () => clickCell(x, y, z));
                cube.addEventListener('contextmenu', (e) => {
                    e.preventDefault();
                    flagCell(x, y, z);
                });
            }
        }
    }

    // 添加轨道控制器
    controls = new THREE.OrbitControls(camera, renderer.domElement);

    // 渲染循环
    function animate() {
        requestAnimationFrame(animate);
        controls.update();
        renderer.render(scene, camera);
    }
    animate();
}

function clickCell(x, y, z) {
    if (gameOver || gameBoard[z][y][x].revealed || gameBoard[z][y][x].flagged) return;
    if (gameBoard[z][y][x].hasMine) {
        gameOver = true;
        revealAllMines();
        alert('游戏结束，你踩到雷了！');
    } else {
        gameBoard[z][y][x].revealed = true;
        if (gameBoard[z][y][x].minesAround === 0) {
            floodFill(x, y, z);
        }
        updateCubeAppearance(x, y, z);
        checkWin();
    }
}

function flagCell(x, y, z) {
    if (gameOver || gameBoard[z][y][x].revealed) return;
    gameBoard[z][y][x].flagged = !gameBoard[z][y][x].flagged;
    updateCubeAppearance(x, y, z);
}

function floodFill(x, y, z) {
    for (let dz = -1; dz <= 1; dz++) {
        for (let dy = -1; dy <= 1; dy++) {
            for (let dx = -1; dx <= 1; dx++) {
                if (dz === 0 && dy === 0 && dx === 0) continue;
                let newZ = z + dz;
                let newY = y + dy;
                let newX = x + dx;
                if (newZ >= 0 && newZ < depth && newY >= 0 && newY < height && newX >= 0 && newX < width) {
                    if (!gameBoard[newZ][newY][newX].revealed) {
                        clickCell(newX, newY, newZ);
                    }
                }
            }
        }
    }
}

function revealAllMines() {
    for (let z = 0; z < depth; z++) {
        for (let y = 0; y < height; y++) {
            for (let x = 0; x < width; x++) {
                if (gameBoard[z][y][x].hasMine) {
                    gameBoard[z][y][x].revealed = true;
                    updateCubeAppearance(x, y, z);
                }
            }
        }
    }
}

function checkWin() {
    let unrevealedCells = 0;
    for (let z = 0; z < depth; z++) {
        for (let y = 0; y < height; y++) {
            for (let x = 0; x < width; x++) {
                if (!gameBoard[z][y][x].revealed && !gameBoard[z][y][x].hasMine) {
                    unrevealedCells++;
                }
            }
        }
    }
    if (unrevealedCells === 0) {
        gameOver = true;
        alert('恭喜你，游戏胜利！');
    }
}

function updateCubeAppearance(x, y, z) {
    const cube = cubes[z][y][x];
    if (gameBoard[z][y][x].revealed) {
        if (gameBoard[z][y][x].hasMine) {
            cube.material.color.set(0xff0000);
        } else {
            cube.material.color.set(0x888888);
            // 这里可以添加显示周围雷数的逻辑，例如使用标签
        }
    } else if (gameBoard[z][y][x].flagged) {
        cube.material.color.set(0xffff00);
    } else {
        cube.material.color.set(0x00ff00);
    }
}
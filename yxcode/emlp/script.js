// 游戏状态对象
const gameState = {
    player: {
        health: 0,
        props: {
            knife: 0,
            handcuffs: 0,
            phone: 0,
            soda: 0,
            magnifier: 0,
            medicine: 0
        }
    },
    computer: {
        health: 0,
        props: {
            knife: 0,
            handcuffs: 0,
            phone: 0,
            soda: 0,
            magnifier: 0,
            medicine: 0
        }
    },
    bullets: {
        real: 0,
        fake: 0,
        total: 0,
        current: 1,
        list: [] // 存储每发子弹的真假，1为真，0为假
    },
    damage: 1,
    target: -1, // 1向电脑开枪，2向自己开枪
    turn: false, // false为玩家回合，true为电脑回合
    isGameStarted: false
};

// DOM元素
const dom = {
    playerHealth: document.getElementById('player-health'),
    computerHealth: document.getElementById('computer-health'),
    playerProps: {
        knife: document.getElementById('player-knife'),
        handcuffs: document.getElementById('player-handcuffs'),
        phone: document.getElementById('player-phone'),
        soda: document.getElementById('player-soda'),
        magnifier: document.getElementById('player-magnifier'),
        medicine: document.getElementById('player-medicine')
    },
    computerProps: {
        knife: document.getElementById('computer-knife'),
        handcuffs: document.getElementById('computer-handcuffs'),
        phone: document.getElementById('computer-phone'),
        soda: document.getElementById('computer-soda'),
        magnifier: document.getElementById('computer-magnifier'),
        medicine: document.getElementById('computer-medicine')
    },
    currentTurn: document.getElementById('current-turn'),
    currentBullet: document.getElementById('current-bullet'),
    totalBullets: document.getElementById('total-bullets'),
    realBullets: document.getElementById('real-bullets'),
    fakeBullets: document.getElementById('fake-bullets'),
    messageBox: document.getElementById('message-box'),
    buttons: {
        useKnife: document.getElementById('use-knife'),
        useHandcuffs: document.getElementById('use-handcuffs'),
        usePhone: document.getElementById('use-phone'),
        useSoda: document.getElementById('use-soda'),
        useMagnifier: document.getElementById('use-magnifier'),
        useMedicine: document.getElementById('use-medicine'),
        shootComputer: document.getElementById('shoot-computer'),
        shootPlayer: document.getElementById('shoot-player'),
        startGame: document.getElementById('start-game'),
        restartGame: document.getElementById('restart-game')
    }
};

// 工具函数
function randomInt(min, max) {
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

function showMessage(message, type = 'info') {
    const messageElement = document.createElement('div');
    messageElement.classList.add('message');
    messageElement.classList.add(`${type}-message`);
    messageElement.textContent = message;
    dom.messageBox.appendChild(messageElement);
    dom.messageBox.scrollTop = dom.messageBox.scrollHeight;
}

function updateUI() {
    // 更新血量
    dom.playerHealth.textContent = gameState.player.health;
    dom.computerHealth.textContent = gameState.computer.health;

    // 更新道具
    for (const prop in dom.playerProps) {
        dom.playerProps[prop].textContent = gameState.player.props[prop];
    }
    for (const prop in dom.computerProps) {
        dom.computerProps[prop].textContent = gameState.computer.props[prop];
    }

    // 更新子弹信息
    dom.currentBullet.textContent = gameState.bullets.current;
    dom.totalBullets.textContent = gameState.bullets.total;
    dom.realBullets.textContent = gameState.bullets.real;
    dom.fakeBullets.textContent = gameState.bullets.fake;

    // 更新回合信息
    dom.currentTurn.textContent = gameState.turn ? '电脑' : '玩家';

    // 更新按钮状态
    updateButtonStates();
}

function updateButtonStates() {
    // 禁用所有道具按钮
    for (const btn in dom.buttons) {
        if (btn.startsWith('use') || btn.startsWith('shoot')) {
            dom.buttons[btn].disabled = true;
        }
    }

    if (!gameState.isGameStarted) return;

    // 如果是玩家回合，启用相应按钮
    if (!gameState.turn) {
        // 启用道具按钮（如果有道具）
        for (const prop in gameState.player.props) {
            if (gameState.player.props[prop] > 0) {
                dom.buttons[`use${prop.charAt(0).toUpperCase() + prop.slice(1)}`].disabled = false;
            }
        }
        // 启用开枪按钮
        dom.buttons.shootComputer.disabled = false;
        dom.buttons.shootPlayer.disabled = false;
    }
}

// 道具函数
function useKnife(player = false) {
    if (player) {
        if (gameState.player.props.knife <= 0) return;
        gameState.player.props.knife--;
        showMessage('你使用了刀，下一发伤害+1！');
    } else {
        if (gameState.computer.props.knife <= 0) return;
        gameState.computer.props.knife--;
        showMessage('电脑使用了刀，下一发伤害+1！');
    }
    gameState.damage++;
    updateUI();
}

function useHandcuffs(player = false) {
    if (player) {
        if (gameState.player.props.handcuffs <= 0) return;
        gameState.player.props.handcuffs--;
        showMessage('你使用了手铐，电脑被困住了！');
    } else {
        if (gameState.computer.props.handcuffs <= 0) return;
        gameState.computer.props.handcuffs--;
        showMessage('电脑使用了手铐，你被困住了！');
    }
    gameState.turn = player;
    updateUI();
}

function usePhone(player = false) {
    if (player) {
        if (gameState.player.props.phone <= 0) return;
        gameState.player.props.phone--;
        const bulletNum = randomInt(1, gameState.bullets.total);
        const isReal = gameState.bullets.list[bulletNum - 1] === 1;
        showMessage(`你使用了电话，第${bulletNum}发子弹是${isReal ? '真' : '假'}的！`);
    } else {
        if (gameState.computer.props.phone <= 0) return;
        gameState.computer.props.phone--;
        const bulletNum = randomInt(1, gameState.bullets.total);
        const isReal = gameState.bullets.list[bulletNum - 1] === 1;
        showMessage(`电脑使用了电话，第${bulletNum}发子弹是${isReal ? '真' : '假'}的！`);
    }
    updateUI();
}

function useSoda(player = false) {
    if (player) {
        if (gameState.player.props.soda <= 0) return;
        gameState.player.props.soda--;
        showMessage('你使用了汽水，退掉了一发子弹！');
    } else {
        if (gameState.computer.props.soda <= 0) return;
        gameState.computer.props.soda--;
        showMessage('电脑使用了汽水，退掉了一发子弹！');
    }
    gameState.bullets.current++;
    if (gameState.bullets.current > gameState.bullets.total) {
        generateNewBulletsAndProps();
    }
    updateUI();
}

function useMagnifier(player = false) {
    if (player) {
        if (gameState.player.props.magnifier <= 0) return;
        gameState.player.props.magnifier--;
        const isReal = gameState.bullets.list[gameState.bullets.current - 1] === 1;
        showMessage(`你使用了放大镜，当前发子弹是${isReal ? '真' : '假'}的！`);
    } else {
        if (gameState.computer.props.magnifier <= 0) return;
        gameState.computer.props.magnifier--;
        const isReal = gameState.bullets.list[gameState.bullets.current - 1] === 1;
        showMessage(`电脑使用了放大镜，当前发子弹是${isReal ? '真' : '假'}的！`);
    }
    updateUI();
}

function useMedicine(player = false) {
    if (player) {
        if (gameState.player.props.medicine <= 0) return;
        gameState.player.props.medicine--;
        gameState.player.health++;
        showMessage('你使用了药，恢复了1点血量！');
    } else {
        if (gameState.computer.props.medicine <= 0) return;
        gameState.computer.props.medicine--;
        gameState.computer.health++;
        showMessage('电脑使用了药，恢复了1点血量！');
    }
    updateUI();
}

// 电脑选择使用道具
function computerUseProp() {
    const availableProps = [];
    for (const prop in gameState.computer.props) {
        if (gameState.computer.props[prop] > 0) {
            availableProps.push(prop);
        }
    }

    if (availableProps.length === 0) {
        showMessage('电脑没有可用的道具！');
        return;
    }

    const choice = availableProps[randomInt(0, availableProps.length - 1)];

    switch (choice) {
        case 'knife':
            useKnife(false);
            break;
        case 'handcuffs':
            useHandcuffs(false);
            break;
        case 'phone':
            usePhone(false);
            break;
        case 'soda':
            useSoda(false);
            break;
        case 'magnifier':
            useMagnifier(false);
            break;
        case 'medicine':
            useMedicine(false);
            break;
    }
}

// 生成新道具
function generateNewProps() {
    // 清空现有道具
    for (const prop in gameState.player.props) {
        gameState.player.props[prop] = 0;
        gameState.computer.props[prop] = 0;
    }

    // 随机生成道具数量
    const propCount = randomInt(2, 10);
    for (let i = 0; i < propCount; i++) {
        const propType = randomInt(1, 6);
        switch (propType) {
            case 1:
                gameState.player.props.knife++;
                gameState.computer.props.knife++;
                break;
            case 2:
                gameState.player.props.handcuffs++;
                gameState.computer.props.handcuffs++;
                break;
            case 3:
                gameState.player.props.phone++;
                gameState.computer.props.phone++;
                break;
            case 4:
                gameState.player.props.soda++;
                gameState.computer.props.soda++;
                break;
            case 5:
                gameState.player.props.magnifier++;
                gameState.computer.props.magnifier++;
                break;
            case 6:
                gameState.player.props.medicine++;
                gameState.computer.props.medicine++;
                break;
        }
    }

    showMessage(`生成了新道具：玩家和电脑各获得${propCount}个道具`);
    updateUI(); // 确保生成新道具后立即更新UI和按钮状态
}

// 生成新子弹
function generateNewBullets() {
    gameState.bullets.list = [];

    // 随机生成真子弹和假子弹数量
    gameState.bullets.real = randomInt(1, 6);
    gameState.bullets.fake = randomInt(1, 6);
    gameState.bullets.total = gameState.bullets.real + gameState.bullets.fake;

    // 初始化子弹数组
    for (let i = 0; i < gameState.bullets.total; i++) {
        gameState.bullets.list.push(-1);
    }

    // 随机分配真子弹位置
    let realCount = 0;
    while (realCount < gameState.bullets.real) {
        const index = randomInt(0, gameState.bullets.total - 1);
        if (gameState.bullets.list[index] === -1) {
            gameState.bullets.list[index] = 1;
            realCount++;
        }
    }

    // 分配假子弹位置
    for (let i = 0; i < gameState.bullets.total; i++) {
        if (gameState.bullets.list[i] === -1) {
            gameState.bullets.list[i] = 0;
        }
    }

    showMessage(`生成了新子弹：${gameState.bullets.real}发真子弹，${gameState.bullets.fake}发假子弹`);
}

// 生成新子弹和道具
function generateNewBulletsAndProps() {
    gameState.bullets.current = 1;
    generateNewBullets();
    generateNewProps();
    updateUI();
}

// 射击函数
function shoot(target) {
    if (!gameState.isGameStarted) return;

    gameState.target = target;
    const isReal = gameState.bullets.list[gameState.bullets.current - 1] === 1;
    showMessage(`第${gameState.bullets.current}发子弹是${isReal ? '真' : '假'}子弹！`);

    // 计算伤害
    const damage = gameState.damage * (isReal ? 1 : 0);
    if (target === 1) {
        gameState.computer.health -= damage;
        showMessage(`你向电脑开枪，${damage > 0 ? `造成${damage}点伤害` : '没有造成伤害'}`);
    } else {
        gameState.player.health -= damage;
        showMessage(`你向自己开枪，${damage > 0 ? `造成${damage}点伤害` : '没有造成伤害'}`);
    }

    // 检查游戏是否结束
    if (gameState.player.health <= 0 && gameState.computer.health <= 0) {
        showMessage('双方同归于尽！', 'warning');
        gameState.isGameStarted = false;
    } else if (gameState.player.health <= 0) {
        showMessage('电脑赢了！', 'warning');
        gameState.isGameStarted = false;
    } else if (gameState.computer.health <= 0) {
        showMessage('你赢了！', 'success');
        gameState.isGameStarted = false;
    } else {
        // 回合结束，进入下一发
        gameState.bullets.current++;
        gameState.turn = !gameState.turn;
        gameState.damage = 1;

        // 检查是否需要重新生成子弹
        if (gameState.bullets.current > gameState.bullets.total) {
            showMessage('子弹用完了，重新生成子弹和道具！');
            generateNewBulletsAndProps();
        } else if (gameState.turn) {
            // 电脑回合
            setTimeout(computerTurn, 1000);
        }
    }

    updateUI();
}

// 电脑回合
function computerTurn() {
    if (!gameState.isGameStarted) return;

    showMessage('电脑回合开始！');
    // 电脑随机选择是否使用道具
    if (Math.random() > 0.3) {
        computerUseProp();
    } else {
        showMessage('电脑没有使用道具！');
    }

    // 电脑随机选择射击目标
    const target = randomInt(1, 2);
    showMessage(`电脑选择向${target === 1 ? '自己' : '你'}开枪`);

    // 执行射击
    setTimeout(() => shoot(target), 1000);
}

// 开始游戏
function startGame() {
    // 重置游戏状态
    gameState.player.health = 5; // 默认血量
    gameState.computer.health = 5;
    gameState.damage = 1;
    gameState.target = -1;
    gameState.turn = false; // 玩家先开始
    gameState.isGameStarted = true;

    // 清空消息框
    dom.messageBox.innerHTML = '';

    // 生成初始子弹和道具
    generateNewBulletsAndProps();

    showMessage('游戏开始！祝你好运！', 'success');
    updateUI();
}

// 事件监听
dom.buttons.useKnife.addEventListener('click', () => useKnife(true));
dom.buttons.useHandcuffs.addEventListener('click', () => useHandcuffs(true));
dom.buttons.usePhone.addEventListener('click', () => usePhone(true));
dom.buttons.useSoda.addEventListener('click', () => useSoda(true));
dom.buttons.useMagnifier.addEventListener('click', () => useMagnifier(true));
dom.buttons.useMedicine.addEventListener('click', () => useMedicine(true));
dom.buttons.shootComputer.addEventListener('click', () => shoot(1));
dom.buttons.shootPlayer.addEventListener('click', () => shoot(2));
dom.buttons.startGame.addEventListener('click', startGame);
dom.buttons.restartGame.addEventListener('click', startGame);

// 初始化UI
updateUI();
showMessage('欢迎来到子弹游戏！点击"开始游戏"按钮开始新游戏。', 'info');
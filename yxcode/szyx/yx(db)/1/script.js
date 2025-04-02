const questions = [
    { question: "1 + 1 = ?", answer: "2" },
    { question: "2 * 3 = ?", answer: "6" },
    { question: "5 - 2 = ?", answer: "3" }
];

let currentQuestionIndex = 0;
let score = 0;
let timeLeft = 60;
let timer;

// 显示题目
function showQuestion() {
    const questionElement = document.getElementById('question');
    if (currentQuestionIndex < questions.length) {
        questionElement.textContent = questions[currentQuestionIndex].question;
    } else {
        questionElement.textContent = "游戏结束！";
    }
}

// 验证答案
function checkAnswer() {
    const answerInput = document.getElementById('answer');
    const userAnswer = answerInput.value;
    const correctAnswer = questions[currentQuestionIndex].answer;
    if (userAnswer === correctAnswer) {
        score++;
        const scoreValue = document.getElementById('score-value');
        scoreValue.textContent = score;
    }
    currentQuestionIndex++;
    answerInput.value = '';
    showQuestion();
}

// 倒计时
function startTimer() {
    timer = setInterval(() => {
        timeLeft--;
        const timeLeftElement = document.getElementById('time-left');
        timeLeftElement.textContent = timeLeft;
        if (timeLeft === 0) {
            clearInterval(timer);
            document.getElementById('question').textContent = "时间到！游戏结束！";
            document.getElementById('submit').disabled = true;
        }
    }, 1000);
}

// 重新开始游戏
function restartGame() {
    currentQuestionIndex = 0;
    score = 0;
    timeLeft = 60;
    const scoreValue = document.getElementById('score-value');
    scoreValue.textContent = score;
    const timeLeftElement = document.getElementById('time-left');
    timeLeftElement.textContent = timeLeft;
    document.getElementById('submit').disabled = false;
    showQuestion();
    clearInterval(timer);
    startTimer();
}

// 初始化游戏
showQuestion();
startTimer();

// 绑定事件
const submitButton = document.getElementById('submit');
submitButton.addEventListener('click', checkAnswer);

const restartButton = document.getElementById('restart');
restartButton.addEventListener('click', restartGame);
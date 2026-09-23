// server/utils/captcha.js

async function verifyHumanToken(token) {
    const verifyUrl = process.env.CAPTCHA_VERIFY_URL;

    if (!verifyUrl) {
        if (process.env.NODE_ENV !== 'production') {
            console.warn('[captcha] 未配置 CAPTCHA_VERIFY_URL，开发环境跳过人机验证');
            return true;
        }
        throw new Error('服务器未配置人机验证服务地址');
    }

    if (!token) return false;

    try {
        const resp = await fetch(verifyUrl, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ token })
        });

        if (!resp.ok) {
            console.error('[captcha] 验证接口返回非 2xx:', resp.status);
            return false;
        }

        const body = await resp.json();

        // SaobbyCaptcha 返回结构：
        //   { data: { result: true/false }, msg: "OK", retcode: 0 }
        if (body.retcode !== undefined && body.retcode !== 0) {
            console.error('[captcha] 验证接口 retcode 非 0:', body);
            return false;
        }

        return !!(body.data && body.data.result === true);
    } catch (err) {
        console.error('[captcha] 验证请求失败:', err.message);
        return false;
    }
}

module.exports = { verifyHumanToken };
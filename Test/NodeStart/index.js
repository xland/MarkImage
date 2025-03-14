const { spawn } = require('child_process');
const p = spawn('D:\\project\\MarkImage_new\\MarkImage\\x64\\Debug\\MarkImage.exe');
p.stdout.on('data', (data) => {
    console.log(`输出: ${data.toString()}`);
});
p.stderr.on('data', (data) => {
    console.error(`错误: ${data.toString()}`);
});
p.on('close', (code) => {
    console.log(`进程结束，退出码: ${code}`);
});
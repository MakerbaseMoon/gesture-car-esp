const gateway = `ws://${window.location.hostname}/ws`;
let websocket;

const ForwardLeft = document.getElementById('ForwardLeft');
const Forward = document.getElementById('Forward');
const ForwardRight = document.getElementById('ForwardRight');

const StrafeLeft = document.getElementById('StrafeLeft');
const Stop = document.getElementById('Stop');
const StrafeRight = document.getElementById('StrafeRight');

const BackwardLeft = document.getElementById('BackwardLeft');
const Backward = document.getElementById('Backward');
const BackwardRight = document.getElementById('BackwardRight');

const TurnLeft = document.getElementById('TurnLeft');
const TurnRight = document.getElementById('TurnRight');

window.addEventListener('load', onload);

function onload(event) {
    initWebSocket();
}

function initWebSocket() {
    console.log('Trying to open aWebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen = onOpen;
    websocket.onclose = onClose;
    websocket.onmessage = onMessage;
}

function onOpen(event) {
    console.log('Connection opened');
}

function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
}

function onMessage(event) {
    console.log('Message from server:', event.data);
}

function sendCommand(command) {
    websocket.send(command);
    // fetch(`/${command}`, {
    //     method: 'GET',
    // })
    // .then((response) => response.text())
    // .then(data => {
    //     console.log(`ESP32: ${data}`);
    // })
    // .catch(error => {
    //     console.error('Fetch error:', error);
    // }); 
}

//第一行
ForwardLeft.addEventListener('mousedown', () => {
    sendCommand('ForwardLeft');
    console.log('Starting ForwardLeft');
});
ForwardLeft.addEventListener('mouseup', () => {
    sendCommand('Stop');
    console.log('Stopping ForwardLeft');
});
ForwardLeft.addEventListener('touchstart', () => {
    sendCommand('ForwardLeft');
    console.log('Starting ForwardLeft(touch)');
});
ForwardLeft.addEventListener('touchend', () => {
    sendCommand('Stop');
    console.log('Stopping ForwardLeft(touch)');
});

Forward.addEventListener('mousedown', () => {
    sendCommand('Forward');
    console.log('Starting Forward');
});
Forward.addEventListener('mouseup', () => {
    sendCommand('Stop');
    console.log('Stopping Forward');
});
Forward.addEventListener('touchstart', () => {
    sendCommand('Forward');
    console.log('Starting Forward(touch)');
});
Forward.addEventListener('touchend', () => {
    sendCommand('Stop');
    console.log('Stopping Forward(touch)');
});

ForwardRight.addEventListener('mousedown', () => {
    sendCommand('ForwardRight');
    console.log('Starting ForwardRight');
});
ForwardRight.addEventListener('mouseup', () => {
    sendCommand('Stop');
    console.log('Stopping ForwardRight');
});
ForwardRight.addEventListener('touchstart', () => {
    sendCommand('ForwardRight');
    console.log('Starting ForwardRight(touch)');
});
ForwardRight.addEventListener('touchend', () => {
    sendCommand('Stop');
    console.log('Stopping ForwardRight(touch)');
});
//第二行
StrafeLeft.addEventListener('mousedown', () => {
    sendCommand('StrafeLeft');
    console.log('Starting StrafeLeft');
});
StrafeLeft.addEventListener('mouseup', () => {
    sendCommand('Stop');
    console.log('Stopping StrafeLeft');
});
StrafeLeft.addEventListener('touchstart', () => {
    sendCommand('StrafeLeft');
    console.log('Starting StrafeLeft(touch)');
});
StrafeLeft.addEventListener('touchend', () => {
    sendCommand('Stop');
    console.log('Stopping StrafeLeft(touch)');
});

Stop.addEventListener('mousedown', () => {
    sendCommand('Stop');
    console.log('Starting Stop');
});
Stop.addEventListener('mouseup', () => {
    sendCommand('Stop');
    console.log('Stopping Stop');
});
Stop.addEventListener('touchstart', () => {
    sendCommand('Stop');
    console.log('Starting Stop(touch)');
});
Stop.addEventListener('touchend', () => {
    sendCommand('Stop');
    console.log('Stopping Stop(touch)');
});

StrafeRight.addEventListener('mousedown', () => {
    sendCommand('StrafeRight');
    console.log('Starting StrafeRight');
});
StrafeRight.addEventListener('mouseup', () => {
    sendCommand('Stop');
    console.log('Stopping StrafeRight');
});
StrafeRight.addEventListener('touchstart', () => {
    sendCommand('StrafeRight');
    console.log('Starting StrafeRight(touch)');
});
StrafeRight.addEventListener('touchend', () => {
    sendCommand('Stop');
    console.log('Stopping StrafeRight(touch)');
});
//第三行
BackwardLeft.addEventListener('mousedown', () => {
    sendCommand('BackwardLeft');
    console.log('Starting BackwardLeft');
});
BackwardLeft.addEventListener('mouseup', () => {
    sendCommand('Stop');
    console.log('Stopping BackwardLeft');
});
BackwardLeft.addEventListener('touchstart', () => {
    sendCommand('BackwardLeft');
    console.log('Starting BackwardLeft(touch)');
});
BackwardLeft.addEventListener('touchend', () => {
    sendCommand('Stop');
    console.log('Stopping BackwardLeft(touch)');
});

Backward.addEventListener('mousedown', () => {
    sendCommand('Backward');
    console.log('Starting Backward');
});
Backward.addEventListener('mouseup', () => {
    sendCommand('Stop');
    console.log('Stopping Backward');
});
Backward.addEventListener('touchstart', () => {
    sendCommand('Backward');
    console.log('Starting Backward(touch)');
});
Backward.addEventListener('touchend', () => {
    sendCommand('Stop');
    console.log('Stopping Backward(touch)');
});

BackwardRight.addEventListener('mousedown', () => {
    sendCommand('BackwardRight');
    console.log('Starting BackwardRight');
});
BackwardRight.addEventListener('mouseup', () => {
    sendCommand('Stop');
    console.log('Stopping BackwardRight');
});
BackwardRight.addEventListener('touchstart', () => {
    sendCommand('BackwardRight');
    console.log('Starting BackwardRight(touch)');
});
BackwardRight.addEventListener('touchend', () => {
    sendCommand('Stop');
    console.log('Stopping BackwardRight(touch)');
});
//第四行
TurnLeft.addEventListener('mousedown', () => {
    sendCommand('TurnLeft');
    console.log('Starting TurnLeft');
});
TurnLeft.addEventListener('mouseup', () => {
    sendCommand('Stop');
    console.log('Stopping TurnLeft');
});
TurnLeft.addEventListener('touchstart', () => {
    sendCommand('TurnLeft');
    console.log('Starting TurnLeft(touch)');
});
TurnLeft.addEventListener('touchend', () => {
    sendCommand('Stop');
    console.log('Stopping TurnLeft(touch)');
});

TurnRight.addEventListener('mousedown', () => {
    sendCommand('TurnRight');
    console.log('Starting TurnRight');
});
TurnRight.addEventListener('mouseup', () => {
    sendCommand('Stop');
    console.log('Stopping TurnRight');
});
TurnRight.addEventListener('touchstart', () => {
    sendCommand('TurnRight');
    console.log('Starting TurnRight(touch)');
});
TurnRight.addEventListener('touchend', () => {
    sendCommand('Stop');
    console.log('Stopping TurnRight(touch)');
});
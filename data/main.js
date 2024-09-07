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

function sendCommand(command) {
    fetch(`/${command}`, {
        method: 'GET',
    })
    .then((response) => response.text())
    .then(data => {
        console.log(`ESP32: ${data}`);
    })
    .catch(error => {
        console.error('Fetch error:', error);
    });
}

ForwardLeft.addEventListener('click', () => sendCommand('ForwardLeft'));
Forward.addEventListener('click', () => sendCommand('Forward'));
ForwardRight.addEventListener('click', () => sendCommand('ForwardRight'));

StrafeLeft.addEventListener('click', () => sendCommand('StrafeLeft'));
Stop.addEventListener('click', () => sendCommand('Stop'));
StrafeRight.addEventListener('click', () => sendCommand('StrafeRight'));

BackwardLeft.addEventListener('click', () => sendCommand('BackwardLeft'));
Backward.addEventListener('click', () => sendCommand('Backward'));
BackwardRight.addEventListener('click', () => sendCommand('BackwardRight'));

TurnLeft.addEventListener('click', () => sendCommand('TurnLeft'));
TurnRight.addEventListener('click', () => sendCommand('TurnRight'));
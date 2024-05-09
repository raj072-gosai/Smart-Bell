
char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<head>
  <title>L J WirelessBell</title>
  <style>
    body {
      background: rgb(246, 250, 255);
      font-family: 'Arial', sans-serif;
      margin: 0;
      text-align: center;
    }

    table {
      padding: 10px;
    }

    td {
      padding: 5px;
    }

    .b2 {
      font-size: 20px;
      border-radius: 12px;
      background-color: #fa0303;
      color: #fff;
      padding: 10px 10px;
      cursor: pointer;
      border: 4px solid #fa0303;
      width: 100%;
      height: 50px;
      margin-bottom: 10px;
      transition: transform 0.3s ease-in-out, background-color 0.3s ease-in-out;
    }

    .b2:hover {
      transform: scale(1.1);
      background-color: #fa0303;
    }

    .send {
      font-size: 20px;
      border-radius: 12px;
      background-color: green;
      color: #fff;
      padding: 10px 10px;
      cursor: pointer;
      border: 4px solid green;
      width: 100%;
      height: 50px;
      margin-bottom: 10px;
      transition: transform 0.3s ease-in-out, background-color 0.3s ease-in-out;
    }

    .send:hover {
      transform: scale(1.1);
      background-color: green;
    }

    .container {
      display: flex;
      flex-direction: column;
      align-items: center;
      justify-content: center;
      height: 100vh;
      box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
    }

    .header {
      font-size: 36px;
      margin-bottom: 10px;
      color: #000;
    }

    .input-container {
      margin-top: 10px;
    }

    input {
      font-size: 18px;
      padding: 12px;
      width: 250px;
      border: 2px solid #3282ff;
      border-radius: 8px;
      outline: none;
      margin-bottom: 10px;
      transition: border-color 0.3s ease-in-out;
    }

    input:focus {
      border-color: #011585;
    }

    .button {
      font-size: 20px;
      border-radius: 12px;
      background-color: #3282ff;
      color: #fff;
      padding: 10px 10px;
      cursor: pointer;
      border: 4px solid #3282ff;
      width: 200px;
      margin-bottom: 10px;
      transition: transform 0.3s ease-in-out, background-color 0.3s ease-in-out;
    }

    .b1 {
      font-size: 20px;
      border-radius: 10%;
      background-color: #3282ff;
      color: #fff;
      padding: 20px;
      cursor: pointer;
      border: 4px solid #3282ff;
      margin: 15px;
      transition: transform 0.3s ease-in-out, background-color 0.3s ease-in-out;
    }

    .button:hover,
    .b1:hover {
      transform: scale(1.1);
      background-color: #3282ff;
    }
  </style>
  <script>
    function checkInputLength(inputField) {
      var userInput = inputField.value;
      var errorMessage = document.getElementById("error-message");

      if (userInput.length > 20) {
        errorMessage.textContent = "Error: Maximum 20 characters allowed.";
        inputField.value = userInput.slice(0, 20); // Truncate to 10 characters
      }
      else {
        errorMessage.textContent = ""; // Clear error message
      }
    }
  </script>
</head>

<body>
  <center>
    <h1>
      <h1>LJ WIRELESSBELL</h1>
    </h1>
    <h1 id="btn_msg"></h1>
    <table>
      <tr>
        <td> <input type="text" id="numberInput" name="numberInput" min="0" max="9" maxlength="14"
            placeholder="Type Here Any Message" oninput="checkInputLength(this)">
          <br>
          <p id="error-message" style="color: red;"></p>
        </td>

        <td><button class="button" onclick="repeatMessage()">REPEAT</button><br></td>
        <td>
          <button class="button" onclick="appendMessage('COME   ')">COME</button><br>
        </td>
      </tr>
      <tr>
        <td>
          <button class="b1" onclick="appendNumber(' 1')">1</button>
          <button class="b1" onclick="appendNumber(' 2')">2</button>
          <button class="b1" onclick="appendNumber(' 3')">3</button><br>
        </td>
        <td>
          <button class="button" onclick="appendMessage('TEA    ')">TEA</button><br>
        </td>
        <td>
          <button class="button" onclick="appendMessage('NEXT   ')">NEXT</button><br>
        </td>
      </tr>
      <tr>
        <td>
          <button class="b1" onclick="appendNumber(' 4')">4</button>
          <button class="b1" onclick="appendNumber(' 5')">5</button>
          <button class="b1" onclick="appendNumber(' 6')">6</button><br>
        </td>
        <td>
          <button class="button" onclick="appendMessage('COFFEE ')">COFFEE</button><br>
        </td>
        <td>
          <button class="button" onclick="appendMessage('CALL   ')">CALL</button>
        </td>
      </tr>
      <tr>
        <td>
          <button class="b1" onclick="appendNumber(' 7')">7</button>
          <button class="b1" onclick="appendNumber(' 8')">8</button>
          <button class="b1" onclick="appendNumber(' 9')">9</button><br>
        </td>
        <td><button class="button" onclick="appendMessage('WATER  ')">WATER</button><br></td>
        <td>
          <button class="button" onclick="appendMessage('COLD-DRINK ')">COLD-DRINK</button>
        </td>
      </tr>
      <tr>
        <td colspan="3" align="center"><button class="send" onclick="sendMessage()">SEND</button></td>
      </tr>
      <tr>
        <td colspan="3" align="center">
          <button class="b2" onclick="appendMessage('EMERGENCY ')">EMERGENCY</button><br>
        </td>
      </tr>
    </table>
  </center>
  <script>
    var connection = new WebSocket('ws://' + location.hostname + ':81/');
    var previousMessage = '';

    function appendNumber(number) {
      document.getElementById('numberInput').value += number;
    }
    function appendMessage(message) {
      if (document.getElementById('numberInput').value.trim() !== '') {
        message = ' ' + message;
      }
      document.getElementById('numberInput').value += message;
    }
        function clearBtnMessage() {
      document.getElementById("btn_msg").innerHTML = "";
    }
    function sendMessage() {
      var message = document.getElementById('numberInput').value;
      console.log("Sending message:", message);
      previousMessage = message;
      connection.send(message);
      document.getElementById('numberInput').value = '';
      // Clear btn_msg immediately when the SEND button is pressed
      clearBtnMessage();
    }
    function repeatMessage() {
      document.getElementById('numberInput').value = previousMessage;
    }
    connection.onmessage = function (event)
    {
      var full_data = event.data;
      console.log(full_data);
      document.getElementById("btn_msg").innerHTML = full_data;
    }
  </script>
</body>

</html>
)=====";
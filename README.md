<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>
  <h1>Mastermind Game</h1>

  <p>This repository contains the implementation of the classic game <strong>Mastermind</strong>. The goal of the game is to guess a secret code made up of colored pegs. The player makes a guess, and the game provides feedback based on how close the guess is to the secret code. The player continues guessing until they correctly identify the code.</p>

  <h2>Features</h2>
  <ul>
    <li>Multiple algorithms implemented to solve the game, including:</li>
    <ul>
      <li>Brute force approach</li>
      <li>Donald Knuth's algorithm</li>
    </ul>
    <li>Random or user-generated secret code</li>
    <li>Scoring system using '@' for correct color and position and 'o' for correct color but wrong position</li>
    <li>OpenMP parallelization for efficient computation</li>
    <li>Comprehensive instructions available within the game</li>
  </ul>

  <h2>How to Play</h2>
  <p>When the game starts, you can choose to either create a secret code or let the computer generate one for you. The objective is to guess the secret code, and after each guess, you'll receive a score indicating how close your guess is to the correct code.</p>

  <p><strong>Scoring:</strong></p>
  <ul>
    <li><strong>@</strong> means a correct color in the correct position</li>
    <li><strong>o</strong> means a correct color but in the wrong position</li>
  </ul>

  <p>The game ends when you correctly guess the secret code, achieving a score with all '@' symbols.</p>

  <h2>Algorithms</h2>
  <h3>Brute Force Algorithm</h3>
  <p>This algorithm generates all possible combinations of the code and systematically checks each one until it finds the correct secret code. While effective, it can take many guesses depending on the length of the code and the number of colors available.</p>

  <h3>Donald Knuth's Algorithm</h3>
  <p>Donald Knuth's algorithm is an optimized approach that minimizes the number of guesses needed to solve the game. It uses a strategy to prune the search space after each guess, aiming to solve the game in the fewest guesses possible.</p>

  <h2>Installation</h2>
  <p>To run this project, clone the repository and compile the code. Make sure you have a C++ compiler that supports OpenMP.</p>

  <pre><code>
  git clone https://github.com/RileyLink/mastermind.git
  cd mastermind
  make
  ./mastermind
  </code></pre>

  <h2>Future Improvements</h2>
  <ul>
    <li>Allow dynamic input for the length of the code and number of colors</li>
    <li>Implement additional solving algorithms</li>
    <li>Improve the user interface</li>
  </ul>

</body>
</html>

<div align="center"><h1>Pipex [125 / 100]</h1></div>

<div align="center">
   <a href="https://github.com/ArthurSobreira/42_pipex" target="_blank">
      <img height=170 src="https://github.com/byaliego/42-project-badges/blob/main/badges/pipexm.png" hspace = "10">
   </a>
</div>

## Summary

> <i>The sixth project in the 42sp fundamentals track, <strong>Pipex</strong>, is based on the creation of a program</i>
> <i>that imitates the shell operator <strong>Pipe</strong>, which takes the return from one command and passes it to the input of another.</i>
> <i>The main objective of this project is to introduce the use of <strong>multiple processes with forks</strong>, </i>
> <i><strong>file descriptor redirection</strong>, <strong>execve</strong> and more.</i>

<br>

## Run the Program

* Make sure you clone the repository with the following command:

```bash
$> git clone git@github.com:ArthurSobreira/42_pipex.git
```

* Once cloned, to compile the program, use the following commands:

```bash
$> make / make bonus
```

<br>

## Mandatory

* To run the mandatory part of the program, just have access to an <strong>input file</strong> (the <strong>output file</strong> is not necessary,
  if one does not exist, the program will create it) and execute the following commands:

```bash
$> ./pipex input_file first_cmd second_cmd2 output_file

# Should behave like:

$> < input_file first_cmd | second_cmd2 > output_file
```

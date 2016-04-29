-------------------------------------------------------------------------------

1. Instructions

- replace any [...] with free text,
  and
- replace the [?] with an X if you have completed that stage,
- replace the [?] with an * if you have attempted that stage, but you know
  it doesn't work completely; document why you think it doesn't work, plus
  what you would do to fix the problem, at the end of the marksheet.

-------------------------------------------------------------------------------

2. Information

So that we can calibrate and improve the assignment in the future, give us
a rough idea how long (in hours) you spent on it *in total*:

effort : [120] hours

-------------------------------------------------------------------------------

3. Citation

Clearly it might have an influence on your mark, but the use of third-party
resources *is* allowed *if* correctly cited (unless explicitly prohibited 
by the assignment description of course).  Let us know what third-party 
source code or resources you used (if any) so it's clear what's your work 
and what isn't:

1.Freedom Embedded. (2010). Using Newlib in ARM bare metal programs. [online] Available at: https://balau82.wordpress.com/2010/12/16/using-newlib-in-arm-bare-metal-programs/ [Accessed 22 Apr. 2016].

2.Anon, (2016). [online] Available at: https://www3.cs.stonybrook.edu/~skiena/392/programs/queue.h [Accessed 22 Apr. 2016].
3. GitHub. (2016). alexcoco/alexsh. [online] Available at: https://github.com/alexcoco/alexsh/blob/master/shell.c [Accessed 22 Apr. 2016].
-------------------------------------------------------------------------------

4. Marking

The following gives a stage-by-stage description of the assignment marking
scheme.  Note this acts as an indicative guideline only, including weights
for each more obvious element (e.g., the functional correctness of a stage).
For example, other elements outside this list *often* warrant an increase
or decrease in marks; examples include hard to quantify features such as
the style or efficiency of a solution.

[x] Stage 1 : pre-emptive operating system kernel                    ( 30%)

    Stage 2 : close generalisations and enhancements
[x]           - fork and exit system calls                           ( 10%)
[x]           - priority based scheduler                             ( 10%)
[*]           - Inter-Process Communication (IPC)                    ( 10%)

    Stage 3 : open  generalisations and enhancements
[*]           - file system based on simplified, emulated disk       ( 40%)
                *OR*
[?]           - kernel port to real, physical hardware               ( 40%)

                                                                     ------
                                                                     (100%)

-------------------------------------------------------------------------------

5. Documentation

Any other documentation, notes or comments that you think are important or
might be easy to overlook (e.g., a subtle issue or technique in associated
source code) should go here:

[Ipc implement interprocess communication  share one int]
[file system implement simple file hierarchy  and enable file to read and write]
-------------------------------------------------------------------------------

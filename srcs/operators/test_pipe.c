nt file_desc[2];

    pipe(file_desc);
    int pipewrite = file_desc[1];
    int piperead = file_desc[0];





	// read input from stdin for the first job
	if (strcmp(cmdinternal->argv[0], "cd") == 0) {
        execute_cd(cmdinternal);
        return;
    }
    else if (strcmp(cmdinternal->argv[0], "prompt") == 0) {
		execute_prompt(cmdinternal);
        return;
	}
    else if (strcmp(cmdinternal->argv[0], "pwd") == 0)
        return execute_pwd(cmdinternal);
    else if(strcmp(cmdinternal->argv[0], "exit") == 0) {
		exit(0);
		return;
	}




	pid_t pid;
    if((pid = fork()) == 0 ) {
		// restore the signals in the child process
		restore_sigint_in_child();

		// store the stdout file desc
        int stdoutfd = dup(STDOUT_FILENO);

		// for bckgrnd jobs redirect stdin from /dev/null
		dup2(fd, STDIN_FILENO);
		if (cmdinternal->stdout_pipe)
            dup2(cmdinternal->pipe_write, STDOUT_FILENO);
		if (execvp(cmdinternal->argv[0], cmdinternal->argv) == -1) {
			// restore the stdout for displaying error message
            dup2(stdoutfd, STDOUT_FILENO);

            printf("Command not found: \'%s\'\n", cmdinternal->argv[0]);
			exit(1);
    }
	ASTreeNode* jobNode = t->right;
	if (!cmdinternal->asynchrnous)
    {
        // wait till the process has not finished
        while (waitpid(pid, NULL, 0) <= 0);
    }




    while (jobNode != NULL && NODETYPE(jobNode->type) == NODE_PIPE)
    {
        close(pipewrite); // close the write end
        pipe(file_desc);
        pipewrite = file_desc[1];





		if (strcmp(cmdinternal->argv[0], "cd") == 0) {
        execute_cd(cmdinternal);
        return;
    }
    else if (strcmp(cmdinternal->argv[0], "prompt") == 0) {
		execute_prompt(cmdinternal);
        return;
	}
    else if (strcmp(cmdinternal->argv[0], "pwd") == 0)
        return execute_pwd(cmdinternal);
    else if(strcmp(cmdinternal->argv[0], "exit") == 0) {
		exit(0);
		return;
	}
	pid_t pid;
    if((pid = fork()) == 0 ) {
		// restore the signals in the child process
		restore_sigint_in_child();

		// store the stdout file desc
        int stdoutfd = dup(STDOUT_FILENO);

		// for bckgrnd jobs redirect stdin from /dev/null
	dup2(fd, STDIN_FILENO);






	if (cmdinternal->stdin_pipe)
            dup2(cmdinternal->pipe_read, STDIN_FILENO);

		// write stdout to pipe if present
        if (cmdinternal->stdout_pipe)
            dup2(cmdinternal->pipe_write, STDOUT_FILENO);

        if (execvp(cmdinternal->argv[0], cmdinternal->argv) == -1) {
			// restore the stdout for displaying error message
            dup2(stdoutfd, STDOUT_FILENO);

            printf("Command not found: \'%s\'\n", cmdinternal->argv[0]);
			exit(1);
        }



if (!cmdinternal->asynchrnous)
    {
        // wait till the process has not finished
        while (waitpid(pid, NULL, 0) <= 0);
    }




	close(piperead);
        piperead = file_desc[0];

        jobNode = jobNode->right;
    }

    piperead = file_desc[0];
    close(pipewrite);

	// write output to stdout for the last job






	if (cmdinternal->argc < 0)
        return;

    // check for built-in commands
    if (strcmp(cmdinternal->argv[0], "cd") == 0) {
        execute_cd(cmdinternal);
        return;
    }
    else if (strcmp(cmdinternal->argv[0], "prompt") == 0) {
		execute_prompt(cmdinternal);
        return;
	}
    else if (strcmp(cmdinternal->argv[0], "pwd") == 0)
        return execute_pwd(cmdinternal);
    else if(strcmp(cmdinternal->argv[0], "exit") == 0) {
		exit(0);
		return;
	}

    pid_t pid;
    if((pid = fork()) == 0 ) {
		// restore the signals in the child process
		restore_sigint_in_child();

		// store the stdout file desc
        int stdoutfd = dup(STDOUT_FILENO);

		// for bckgrnd jobs redirect stdin from /dev/null


dup2(fd, STDOUT_FILENO);

 // read stdin from pipe if present
        if (cmdinternal->stdin_pipe)
            dup2(cmdinternal->pipe_read, STDIN_FILENO);


if (execvp(cmdinternal->argv[0], cmdinternal->argv) == -1) {
			// restore the stdout for displaying error message
            dup2(stdoutfd, STDOUT_FILENO);

            printf("Command not found: \'%s\'\n", cmdinternal->argv[0]);
			exit(1);
        }


if (!cmdinternal->asynchrnous)
    {
        // wait till the process has not finished
        while (waitpid(pid, NULL, 0) <= 0);
    }



	close(piperead);
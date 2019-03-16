#include <stdio.h>
#include <stdlib.h>

#define LINE_MAX_LEN 512
#define ARG_LEN LINE_MAX_LEN

typedef struct process *process_t;
typedef struct job *job_t;
typedef enum arg_type arg_type_t;
typedef struct arg arg_t;

/**
 * arg_type - type of an argument
 *
 * NORMAL: argument string is a normal argument for a process
 * PIPE: '|'
 * INPUT_REDIRECT: '>'
 * OUTPUT_REDIRECT: '<'
 * BACKGROUND: '&'
 * NONE: no argument found, default value
 */
enum arg_type {
	NORMAL,
	PIPE,
	INPUT_REDIRECT,
	OUTPUT_REDIRECT,
	BACKGROUND,
	END,
	NONE = 0
};

/**
 * arg - a single argument from a command line
 *
 * str: character content of argument
 * type: type of argument
 * len: length of argument
 */
struct arg {
	char str[ARG_LEN];
	arg_type_t type;
	size_t len;
};

/**
 * process - a single process that can be executed
 *
 * argv: argument strings of process
 * completed: true if process has completed
 * status: exit status of process
 * nextProcess: pointer to process that output will be redirected to
 */
struct process {
	char **argv;

	short completed;
	int status;

	process_t nextProcess;
};

/**
 * job - a job that can have multiple processes piped together
 *
 * line: full command line for the job
 * inputRedirectFile: name of file for input redirect
 * outputRedirectFile: name of file for output redirect
 * firstProcess: first process in list of processes
 * nextJob: next job in list of background jobs
 */
struct job {
	char *line;

	char *inputRedirectFile;
	char *outputRedirectFile;

	process_t firstProcess;

	job_t nextJob;
};

char inputLine[LINE_MAX_LEN];

job_t firstBackgroundJob;

arg_t arg;


#define cond_free(obj)			\
	do {				\
		if (obj)		\
			free(obj);	\
	} while (0)

#define prompt_user() printf("\nE_shell $ ")

void destroy_job(job_t job)
{
	cond_free(job->line);
	cond_free(job->inputRedirectFile);
	cond_free(job->outputRedirectFile);
	free(job);
}

/**
 * get_process - gets a process from part of a command line
 *
 * This function parses a line for arguments until a process's line is finished.
 * This finish is marked by a pipe, which indicates that a new process's
 * arguments are next, or a newline, which indicates that the command line is
 * finished.
 *
 * parentJob: job where the process will be added to
 * line: pointer to character where the process's arguments begin
 *
 * Returns -1 if parsing error occurs, number of characters read from line
 * otherwise.
 */
int get_process(job_t parentJob, char *line)
{
	do {
		get_arg(line);
	} while (0);
}

/* Convert a command line to a job. */
job_t get_job(char *line)
{
	job_t job = (job_t) calloc(1, sizeof(struct job));
	if (!job)
		return NULL;

	char *lineRemaining = line;
	size_t numCharsRead;

	/* Get all processes from a command line. */
	while (numCharsRead = get_process(job, &lineRemaining) > 0)

	return 0;
}

int start_job(job_t job)
{
	/* TODO */
	return 0;
}

void check_background_jobs(void)
{
	/* TODO */
}

int main(int argc, char **argv)
{
	/* Let user use the E_shell forever. */
	while (1) {
		/* Check if any background jobs have completed. */
		check_background_jobs();

		prompt_user();

		/* Get new command. */
		if (!fgets(inputLine, LINE_MAX_LEN, stdin))
			return -1;

		/* Parse the line to get a job. */
		job_t newJob = get_job(inputLine);

		/* Run the job. */
		if (newJob && start_job(newJob) < 0)
			destroy_job(newJob);
	}
	return 0;
}

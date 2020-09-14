'''
Hans Prieto
CIS 212 Project 2
'''

from sys import argv, stdin, stdout, stderr

i_flag = False # used to set -i flag
v_flag = False # used to set -v flag
c_flag = False # used to set -c flag

def sgrep(pattern: str, files: list) -> None:
    '''
    sgrep searches the named input files (or standard input
    if there are no files) for lines containing the given
    pattern.
    '''
    global i_flag, v_flag, c_flag
   
    # if there are no files, sgrep defaults to standard input.
    if files == []:
        count = 0
        for line in stdin:
            l = ''
            match = ''

            if i_flag:
                l = line.lower()
                pattern = pattern.lower()
            else:
                l = line

            if v_flag:
                if pattern not in l:
                    match = line
                    count += 1
            else:
                if pattern in l:
                    match = line
                    count += 1

            if c_flag == False:
                stdout.write(match) 
    
        if c_flag == True:
            stdout.write(f'{str(count)}\n')

    # reads one file.
    elif len(files) == 1:
        file_name = files.pop(0)
        fr = open(file_name, 'r')
        count = 0

        for line in fr:
            l = ''
            match = ''

            if i_flag:
                l = line.lower()
                pattern = pattern.lower()
            else:
                l = line

            if v_flag:
                if pattern not in l:
                    match = line
                    count += 1
            else:
                if pattern in l:
                    match = line
                    count += 1

            if c_flag == False:
                stdout.write(match)

        if c_flag == True:
           stdout.write(f'{str(count)}\n')

    # reads multiple files.
    elif len(files) > 1:
        for file_name in files:
            count = 0
            fr = open(file_name, 'r')
            
            for line in fr:
                l = ''
                match = ''

                if i_flag:
                    l = line.lower()
                    pattern = pattern.lower()
                else:
                    l = line
                
                if v_flag:
                    if pattern not in l:
                        match = line
                        count += 1
                else:
                    if pattern in l:
                        match = line
                        count += 1

                if c_flag == False:
                    if v_flag:
                        if pattern not in l:
                            stdout.write(f'{file_name}:{match}')
                    else:
                        if pattern in l:
                            stdout.write(f'{file_name}:{match}')

            if c_flag == True:
                stdout.write(f'{file_name}:{str(count)}\n')

def main() -> None:
    '''
    Checks to see if there are any flags specified in argv.
    Checks if there's a string in argv and if there isn't, 
    prints an error message.
    Checks if there are any files specified in argv.
    Calls the sgrep function.
    '''
    global i_flag, v_flag, c_flag
    argc = len(argv)
    i = 1

    while i < argc:
        if argv[i][0] == '-' and len(argv[i]) > 1:
            j = 1
            while j < len(argv[i]):
                if argv[i][j] == 'i':
                    i_flag = True
                elif argv[i][j] == 'v':
                    v_flag = True
                elif argv[i][j] == 'c':
                    c_flag = True
                j += 1
        else:
            break
        i += 1

    if i == argc:
        stderr.write('usage: python3 [options] string [files]\n')
    else:
        pattern = argv[i]
        i += 1
        files = []
        while i < argc:
            files.append(argv[i])
            i += 1
        sgrep(pattern, files)

if __name__ == "__main__":
    main()

import json
  
f_hpp = open('sys_tasks.hpp', 'a')    
f_cpp = open('sys_tasks.cpp', 'a')

hpp_file_body = ''
cpp_file_body = ''


def init_task(tasks):
    
    global hpp_file_body
    global cpp_file_body

    if tasks['taskinit'] == '':
        print("Error: no init function found")
        return 0

    if tasks['taskdeinit'] == '':
        print("Error: no deinit function found")
        return 0
    
    hpp_file_body += 'void SystemInitTasks(void);\n'    
    hpp_file_body += 'void SystemDeInitTasks(void);\n'    
    hpp_file_body += '\n'


    cpp_file_body += '/**\n'
    cpp_file_body += ' * Init tasks\n'
    cpp_file_body += ' * Initialize system tasks\n'
    cpp_file_body += ' */\n'
    cpp_file_body += 'void SystemInitTasks(void) {\n'    
    cpp_file_body += '  ' + tasks['taskinit']['call'] +'();\n' 
    cpp_file_body += '#ifdef ENABLE_SYS_TIMER\n'
    cpp_file_body += 'time_elapsed = 0;\n'
    cpp_file_body += 'max_time_elapsed = 0;\n'
    cpp_file_body += '#endif //ENABLE_SYS_TIMER\n'
    cpp_file_body += '}\n'
    cpp_file_body += '\n'
    cpp_file_body += '\n'
    

    return 1

def rt_tasks(tasks):
    
    global hpp_file_body
    global cpp_file_body

    
    if('rt-tasks' in tasks):
        length = len(tasks['rt-tasks'])
    else:
        hpp_file_body += '#define SYS_TASKS_NUM_OF_THREADS  0\n'
        return 0
    
    #check if there is rt-tasks function if not then return
    if tasks['rt-tasks'] == '':
        print("Warning: no rt tasks found")
        return 0
    
    #initialize number fo tasks
    num_of_tasks = 0
    
    for x in range(length):
        if('task0' in tasks['rt-tasks'][x]): 
            hpp_file_body += 'void SystemTask0(void);\n'
            num_of_tasks = 1            
        if('task1' in tasks['rt-tasks'][x]): 
            hpp_file_body += 'void SystemTask1(void);\n'
            num_of_tasks = 2
        if('task2' in tasks['rt-tasks'][x]): 
            hpp_file_body += 'void SystemTask2(void);\n'
            num_of_tasks = 3
        if('task3' in tasks['rt-tasks'][x]): 
            hpp_file_body += 'void SystemTask3(void);\n'
            num_of_tasks = 4
        if('task4' in tasks['rt-tasks'][x]): 
            hpp_file_body += 'void SystemTask4(void);\n'
            num_of_tasks = 5
    
      
    hpp_file_body += '#define SYS_TASKS_NUM_OF_THREADS          ' + str(num_of_tasks) + '\n'
    hpp_file_body += '\n'

    cpp_file_body += '/**\n'
    cpp_file_body += ' * Task 0 task\n'
    cpp_file_body += ' * execute every cycle to get a real time execution\n'
    cpp_file_body += ' */\n'
    cpp_file_body += 'void SystemTask0(void) {\n'
    cpp_file_body += '\n'
    cpp_file_body += '   static uint16_t thread0_ctr;\n'
    cpp_file_body += '\n'
    cpp_file_body += '#ifdef ENABLE_SYS_TIMER\n'
    cpp_file_body += '   UpdateTimer(&tmr1);\n'
    cpp_file_body += '#endif //ENABLE_SYS_TIMER\n'
    cpp_file_body += '   // 1x calls go here\n'
    
    #1x calls
    #########  10ms calls
    for x in range(length):
        if('task0' in tasks['rt-tasks'][x]):                                    
            if(tasks['rt-tasks'][x]['rate'] == '1'):
                cpp_file_body += '   ' + tasks['rt-tasks'][x]['task0'] + '();\n'                                  
    ############################
    cpp_file_body += '\n'
    
    # 2x calls
    cpp_file_body += '   if ((thread0_ctr % 2) == 0) {\n'
    cpp_file_body += '       // 2x calls go here\n'    
    #########  2x calls
    for x in range(length):
        if('task0' in tasks['rt-tasks'][x]):                                    
            if(tasks['rt-tasks'][x]['rate'] == '2'):
                cpp_file_body += '   ' + tasks['rt-tasks'][x]['task0'] + '();\n'                                  
    ############################
    cpp_file_body += '   }\n' 
    cpp_file_body += '\n'
    
    # 5x calls
    cpp_file_body += '   if ((thread0_ctr % 5) == 0) {\n'
    cpp_file_body += '       // 5x calls go here\n'    
    #########  5x calls
    for x in range(length):
        if('task0' in tasks['rt-tasks'][x]):                                    
            if(tasks['rt-tasks'][x]['rate'] == '5'):
                cpp_file_body += '   ' + tasks['rt-tasks'][x]['task0'] + '();\n'                                  
    ############################
    cpp_file_body += '   }\n' 
    cpp_file_body += '\n'    
    
    # 10x calls
    cpp_file_body += '    if (((thread0_ctr - 2) % 10) == 0) {\n'
    cpp_file_body += '       // 10x calls go here\n'
    #########  100ms calls
    for x in range(length):
        if('task0' in tasks['rt-tasks'][x]):                                    
            if(tasks['rt-tasks'][x]['rate'] == '10'):
                cpp_file_body += '   ' + tasks['rt-tasks'][x]['task0'] + '();\n'                                  
    ############################
    cpp_file_body += '   }\n' 
    cpp_file_body += '\n'


    # 20x calls
    cpp_file_body += '    if (((thread0_ctr - 2) % 20) == 0) {\n'
    cpp_file_body += '       // 10x calls go here\n'
    #########  20x calls
    for x in range(length):
        if('task0' in tasks['rt-tasks'][x]):                                    
            if(tasks['rt-tasks'][x]['rate'] == '20'):
                cpp_file_body += '   ' + tasks['rt-tasks'][x]['task0'] + '();\n'                                  
    ############################
    cpp_file_body += '   }\n' 
    cpp_file_body += '\n'
    
    # 50x calls
    cpp_file_body += '    if (((thread0_ctr - 2) % 50) == 0) {\n'
    cpp_file_body += '       // 50x calls go here\n'
    #########  100ms calls
    for x in range(length):
        if('task0' in tasks['rt-tasks'][x]):                                    
            if(tasks['rt-tasks'][x]['rate'] == '50'):
                cpp_file_body += '   ' + tasks['rt-tasks'][x]['task0'] + '();\n'                                  
    ############################
    cpp_file_body += '   }\n' 
    cpp_file_body += '\n'
    
    
    # 100x calls
    cpp_file_body += '    if (((thread0_ctr - 3) % 100) == 0) {\n'
    cpp_file_body += '       // 100x calls go here\n'
    #########  100x calls
    for x in range(length):
        if('task0' in tasks['rt-tasks'][x]):                                    
            if(tasks['rt-tasks'][x]['rate'] == '100'):
                cpp_file_body += '   ' + tasks['rt-tasks'][x]['task0'] + '();\n'                                  
    ############################
    cpp_file_body += '   }\n'     
    
    
    cpp_file_body += '   // Initial loop executes when the TaskLoopCount is 0\n'
    cpp_file_body += '   if (thread0_ctr >= 9999)\n'
    cpp_file_body += '   {\n'
    cpp_file_body += '       thread0_ctr = 0;\n'
    cpp_file_body += '   }\n'
    cpp_file_body += '   else {\n'
    cpp_file_body += '       thread0_ctr++;;\n'
    cpp_file_body += '   }\n'   
    cpp_file_body += '\n'
    cpp_file_body += '#ifdef ENABLE_SYS_TIMER\n'
    cpp_file_body += '   UpdateTimer(&tmr2);\n'    
    cpp_file_body += '   time_elapsed = GetTimeElapsedUs(&tmr1, &tmr2);\n'
    cpp_file_body += '   if (time_elapsed > max_time_elapsed) {\n'
    cpp_file_body += '      max_time_elapsed = time_elapsed;\n'
    cpp_file_body += '   }\n'
    cpp_file_body += '   DebugLog(time_elapsed, "total time in micros: ");\n'
    cpp_file_body += '   DebugLog(max_time_elapsed, "max time elapsed: ");\n'
    cpp_file_body += '#endif //ENABLE_SYS_TIMER\n'
    cpp_file_body += '\n'
    cpp_file_body += '}\n'
    
    
    
    if(num_of_tasks>1):
        ##############################
        ### Task1 ############    
        cpp_file_body += '/**\n'
        cpp_file_body += ' * Task 1 task\n'
        cpp_file_body += ' * execute every cycle to get a real time execution\n'
        cpp_file_body += ' */\n'
        cpp_file_body += 'void SystemTask1(void) {\n'
        cpp_file_body += '\n'
        cpp_file_body += '\n'
        cpp_file_body += '   static uint16_t thread1_ctr;\n'
        cpp_file_body += '   // 1x calls go here\n'
        
        #########  10ms calls
        for x in range(length):
            if('task1' in tasks['rt-tasks'][x]):                                    
                if(tasks['rt-tasks'][x]['rate'] == '1'):
                    cpp_file_body += '   ' + tasks['rt-tasks'][x]['task1'] + '();\n'                                  
        ############################
        
        cpp_file_body += '\n'    
        cpp_file_body += '   if ((thread1_ctr % 2) == 0) {\n'
        cpp_file_body += '       // 2x calls go here\n'    
        ##### 20 ms calls
        for x in range(length):
            if('task1' in tasks['rt-tasks'][x]):                                    
                if(tasks['rt-tasks'][x]['rate'] == '2'):
                    cpp_file_body += '   ' + tasks['rt-tasks'][x]['task1'] + '();\n'                  
        
        cpp_file_body += '   }\n'
        ###########################
        
        cpp_file_body += '\n'    
        cpp_file_body += '   if (((thread1_ctr - 1) % 5) == 0)  {\n'
        cpp_file_body += '       // 5x calls go here\n'
        
        ##### 50 ms calls
        for x in range(length):
            if('task1' in tasks['rt-tasks'][x]):                                    
                if(tasks['rt-tasks'][x]['rate'] == '5'):
                    cpp_file_body += '   ' + tasks['rt-tasks'][x]['task1'] + '();\n'                     
        
        cpp_file_body += '   }\n'    
        ###########################
    
        cpp_file_body += '\n'    
        cpp_file_body += '    if (((thread1_ctr - 2) % 10) == 0) {\n'
        cpp_file_body += '       // 10x calls go here\n'    
        ##### 100 ms calls
        for x in range(length):
            if('task1' in tasks['rt-tasks'][x]):                                    
                if(tasks['rt-tasks'][x]['rate'] == '10'):
                    cpp_file_body += '   ' + tasks['rt-tasks'][x]['task1'] + '();\n'                     
        
        cpp_file_body += '   }\n'
        ###########################        
        
        cpp_file_body += '\n'    
        cpp_file_body += '    if (((thread1_ctr - 3) % 100) == 0) {\n'
        cpp_file_body += '       // 100x calls go here\n'    
        ##### 1000 ms calls
        for x in range(length):
            if('task1' in tasks['rt-tasks'][x]):                                    
                if(tasks['rt-tasks'][x]['rate'] == '100'):
                    cpp_file_body += '   ' + tasks['rt-tasks'][x]['task1'] + '();\n'                     
        
        cpp_file_body += '   }\n'    
        ###########################   
        
        cpp_file_body += '   // Initial loop executes when the TaskLoopCount is 0\n'
        cpp_file_body += '   if (thread1_ctr >= 9999)\n'
        cpp_file_body += '   {\n'
        cpp_file_body += '       thread1_ctr = 0;\n'
        cpp_file_body += '   }\n'
        cpp_file_body += '   else {\n'
        cpp_file_body += '       thread1_ctr++;;\n'
        cpp_file_body += '   }\n'
        cpp_file_body += '}\n'
        ##################### End Task 1 ########################    
    
    
    if(num_of_tasks>2):
        ##############################
        ### Task2 ############    
        cpp_file_body += '/**\n'
        cpp_file_body += ' * Task 2 task\n'
        cpp_file_body += ' * execute every 10ms to get a real time execution\n'
        cpp_file_body += ' */\n'
        cpp_file_body += 'void SystemTask2(void) {\n'
        cpp_file_body += '\n'
        cpp_file_body += '\n'
        cpp_file_body += '   static uint16_t thread2_ctr;\n'
        cpp_file_body += '   // 1x calls go here\n'    
        #########  10ms calls
        for x in range(length):
            if('task2' in tasks['rt-tasks'][x]):                                    
                if(tasks['rt-tasks'][x]['rate'] == '1'):
                    cpp_file_body += '   ' + tasks['rt-tasks'][x]['task2'] + '();\n'                                  
        ############################    
        cpp_file_body += '\n'    
        cpp_file_body += '   if ((thread2_ctr % 2) == 0) {\n'
        cpp_file_body += '       // 2x calls go here\n'    
        ##### 20 ms calls
        for x in range(length):
            if('task2' in tasks['rt-tasks'][x]):                                    
                if(tasks['rt-tasks'][x]['rate'] == '2'):
                    cpp_file_body += '   ' + tasks['rt-tasks'][x]['task2'] + '();\n'                  
        
        cpp_file_body += '   }\n'
        ###########################    
        cpp_file_body += '\n'    
        cpp_file_body += '   if (((thread2_ctr - 1) % 5) == 0)  {\n'
        cpp_file_body += '       // 5x calls go here\n'    
        ##### 50 ms calls
        for x in range(length):
            if('task2' in tasks['rt-tasks'][x]):                                    
                if(tasks['rt-tasks'][x]['rate'] == '5'):
                    cpp_file_body += '   ' + tasks['rt-tasks'][x]['task2'] + '();\n'                     
        
        cpp_file_body += '   }\n'    
        ###########################
        cpp_file_body += '\n'    
        cpp_file_body += '    if (((thread2_ctr - 2) % 10) == 0) {\n'
        cpp_file_body += '       // 10x calls go here\n'    
        ##### 100 ms calls
        for x in range(length):
            if('task2' in tasks['rt-tasks'][x]):                                    
                if(tasks['rt-tasks'][x]['rate'] == '10'):
                    cpp_file_body += '   ' + tasks['rt-tasks'][x]['task2'] + '();\n'                     
        
        cpp_file_body += '   }\n'
        ###########################        
        
        cpp_file_body += '\n'    
        cpp_file_body += '    if (((thread2_ctr - 3) % 100) == 0) {\n'
        cpp_file_body += '       // 100x calls go here\n'    
        ##### 1000 ms calls
        for x in range(length):
            if('task2' in tasks['rt-tasks'][x]):                                    
                if(tasks['rt-tasks'][x]['rate'] == '100'):
                    cpp_file_body += '   ' + tasks['rt-tasks'][x]['task2'] + '();\n'                     
        
        cpp_file_body += '   }\n'    
        ###########################       
        cpp_file_body += '   // Initial loop executes when the TaskLoopCount is 0\n'
        cpp_file_body += '   if (thread2_ctr >= 9999)\n'
        cpp_file_body += '   {\n'
        cpp_file_body += '       thread2_ctr = 0;\n'
        cpp_file_body += '   }\n'
        cpp_file_body += '   else {\n'
        cpp_file_body += '       thread2_ctr++;;\n'
        cpp_file_body += '   }\n'
        cpp_file_body += '}\n'
        ##################### End Task 2 ########################
        
    
    
    if(num_of_tasks>3):
        ##############################
        ### Task3 ############    
        cpp_file_body += '/**\n'
        cpp_file_body += ' * Task 3 task\n'
        cpp_file_body += ' * execute every cycle to get a real time execution\n'
        cpp_file_body += ' */\n'
        cpp_file_body += 'void SystemTask3(void) {\n'
        cpp_file_body += '\n'
        cpp_file_body += '\n'
        cpp_file_body += '   static uint16_t thread3_ctr;\n'
        cpp_file_body += '   // 1x calls go here\n'
        
        #########  10ms calls
        for x in range(length):
            if('task3' in tasks['rt-tasks'][x]):                                    
                if(tasks['rt-tasks'][x]['rate'] == '1'):
                    cpp_file_body += '   ' + tasks['rt-tasks'][x]['task3'] + '();\n'                                  
        ############################
        
        cpp_file_body += '\n'    
        cpp_file_body += '   if ((thread3_ctr % 2) == 0) {\n'
        cpp_file_body += '       // 2x calls go here\n'    
        ##### 20 ms calls
        for x in range(length):
            if('task3' in tasks['rt-tasks'][x]):                                    
                if(tasks['rt-tasks'][x]['rate'] == '2'):
                    cpp_file_body += '   ' + tasks['rt-tasks'][x]['task3'] + '();\n'                  
        
        cpp_file_body += '   }\n'
        ###########################
        
        cpp_file_body += '\n'    
        cpp_file_body += '   if (((thread3_ctr - 1) % 5) == 0)  {\n'
        cpp_file_body += '       // 5x calls go here\n'
        
        ##### 50 ms calls
        for x in range(length):
            if('task3' in tasks['rt-tasks'][x]):                                    
                if(tasks['rt-tasks'][x]['rate'] == '5'):
                    cpp_file_body += '   ' + tasks['rt-tasks'][x]['task3'] + '();\n'                     
        
        cpp_file_body += '   }\n'    
        ###########################
    
        cpp_file_body += '\n'    
        cpp_file_body += '    if (((thread3_ctr - 2) % 10) == 0) {\n'
        cpp_file_body += '       // 10x calls go here\n'    
        ##### 100 ms calls
        for x in range(length):
            if('task3' in tasks['rt-tasks'][x]):                                    
                if(tasks['rt-tasks'][x]['rate'] == '10'):
                    cpp_file_body += '   ' + tasks['rt-tasks'][x]['task3'] + '();\n'                     
        
        cpp_file_body += '   }\n'
        ###########################        
        
        cpp_file_body += '\n'    
        cpp_file_body += '    if (((thread3_ctr - 3) % 100) == 0) {\n'
        cpp_file_body += '       // 100x calls go here\n'    
        ##### 1000 ms calls
        for x in range(length):
            if('task3' in tasks['rt-tasks'][x]):                                    
                if(tasks['rt-tasks'][x]['rate'] == '100'):
                    cpp_file_body += '   ' + tasks['rt-tasks'][x]['task3'] + '();\n'                     
        
        cpp_file_body += '   }\n'    
        ###########################   
        
        cpp_file_body += '   // Initial loop executes when the TaskLoopCount is 0\n'
        cpp_file_body += '   if (thread3_ctr >= 9999)\n'
        cpp_file_body += '   {\n'
        cpp_file_body += '       thread3_ctr = 0;\n'
        cpp_file_body += '   }\n'
        cpp_file_body += '   else {\n'
        cpp_file_body += '       thread3_ctr++;\n'
        cpp_file_body += '   }\n'
        cpp_file_body += '}\n'
        ##################### End Task 3 ########################
    
    
    if(num_of_tasks>4):
        ##############################
        ### Task4 ############    
        cpp_file_body += '/**\n'
        cpp_file_body += ' * Task 4 task\n'
        cpp_file_body += ' * execute every cycle to get a real time execution\n'
        cpp_file_body += ' */\n'
        cpp_file_body += 'void SystemTask4(void) {\n'
        cpp_file_body += '\n'
        cpp_file_body += '\n'
        cpp_file_body += '   static uint16_t thread4_ctr;\n'
        cpp_file_body += '   // 1x calls go here\n'
        
        #########  10ms calls
        for x in range(length):
            if('task4' in tasks['rt-tasks'][x]):                                    
                if(tasks['rt-tasks'][x]['rate'] == '1'):
                    cpp_file_body += '   ' + tasks['rt-tasks'][x]['task4'] + '();\n'                                  
        ############################
        
        cpp_file_body += '\n'    
        cpp_file_body += '   if ((thread4_ctr % 2) == 0) {\n'
        cpp_file_body += '       // 2x calls go here\n'    
        
        ##### 20 ms calls
        for x in range(length):
            if('task4' in tasks['rt-tasks'][x]):                                    
                if(tasks['rt-tasks'][x]['rate'] == '2'):
                    cpp_file_body += '   ' + tasks['rt-tasks'][x]['task4'] + '();\n'                  
        
        cpp_file_body += '   }\n'
        ###########################
        
        cpp_file_body += '\n'    
        cpp_file_body += '   if (((thread4_ctr - 1) % 5) == 0)  {\n'
        cpp_file_body += '       // 5x calls go here\n'
        
        ##### 50 ms calls
        for x in range(length):
            if('task4' in tasks['rt-tasks'][x]):                                    
                if(tasks['rt-tasks'][x]['rate'] == '5'):
                    cpp_file_body += '   ' + tasks['rt-tasks'][x]['task4'] + '();\n'                     
        
        cpp_file_body += '   }\n'
        
        ###########################
    
        cpp_file_body += '\n'    
        cpp_file_body += '    if (((thread4_ctr - 2) % 10) == 0) {\n'
        cpp_file_body += '       // 10x calls go here\n'
        
        ##### 100 ms calls
        for x in range(length):
            if('task4' in tasks['rt-tasks'][x]):                                    
                if(tasks['rt-tasks'][x]['rate'] == '10'):
                    cpp_file_body += '   ' + tasks['rt-tasks'][x]['task4'] + '();\n'                     
        
        cpp_file_body += '   }\n'
    
        ###########################    
        
        
        cpp_file_body += '\n'    
        cpp_file_body += '    if (((thread4_ctr - 3) % 100) == 0) {\n'
        cpp_file_body += '       // 100x calls go here\n'    
        ##### 1000 ms calls
        for x in range(length):
            if('task4' in tasks['rt-tasks'][x]):                                    
                if(tasks['rt-tasks'][x]['rate'] == '100'):
                    cpp_file_body += '   ' + tasks['rt-tasks'][x]['task4'] + '();\n'                     
        
        cpp_file_body += '   }\n'    
        ###########################   
        
        cpp_file_body += '   // Initial loop executes when the TaskLoopCount is 0\n'
        cpp_file_body += '   if (thread4_ctr >= 9999)\n'
        cpp_file_body += '   {\n'
        cpp_file_body += '       thread4_ctr = 0;\n'
        cpp_file_body += '   }\n'
        cpp_file_body += '   else {\n'
        cpp_file_body += '       thread4_ctr++;\n'
        cpp_file_body += '   }\n'
        cpp_file_body += '}\n'
        ##################### End Task 4 ########################
    

    

def nrt_tasks(tasks):

    global hpp_file_body
    global cpp_file_body

    if('nrt-tasks' in tasks):
        length = len(tasks['nrt-tasks'])
    else:
        hpp_file_body += '#define SYS_NUM_OF_NRT_THREADS_  0\n'
        return 0

    #check if there is nrt-tasks function if not then return
    if tasks['nrt-tasks'] == '':
        print("Warning: no nrt tasks found")
        return 0
    
    for x in range(length):
        if('task0' in tasks['nrt-tasks'][x]):
            hpp_file_body += 'void NrtSystemTask0(void);\n'
            num_of_tasks = 1
        if('task1' in tasks['nrt-tasks'][x]):
            hpp_file_body += 'void NrtSystemTask1(void);\n'
            num_of_tasks = 2
        if('task2' in tasks['nrt-tasks'][x]):
            hpp_file_body += 'void NrtSystemTask2(void);\n'
            num_of_tasks = 3
        if('task3' in tasks['nrt-tasks'][x]):
            hpp_file_body += 'void NrtSystemTask3(void);\n'
            num_of_tasks = 4

    hpp_file_body += '\n'
    hpp_file_body += '#define SYS_NUM_OF_NRT_THREADS_          ' + str(num_of_tasks) + '\n'
    hpp_file_body += '\n'


    cpp_file_body += '/**\n'
    cpp_file_body += ' * Not real time Task 0\n'
    cpp_file_body += ' * this task will be executed in a repetetive manner\n'
    cpp_file_body += ' */\n'
    cpp_file_body += 'void NrtSystemTask0(void) {\n'
    cpp_file_body += '\n'
    #add tasks
    for x in range(length):
        if('task0' in tasks['nrt-tasks'][x]):                                                
                cpp_file_body += '   ' + tasks['nrt-tasks'][x]['task0'] + '();\n'   
    cpp_file_body += '}\n'
    cpp_file_body += '\n'
    cpp_file_body += '\n'

    
    if('task1' in tasks['nrt-tasks'][x]): 
        cpp_file_body += '/**\n'
        cpp_file_body += ' * Not real time Task 1\n'
        cpp_file_body += ' * this task will be executed in a repetetive manner\n'
        cpp_file_body += ' */\n'
        cpp_file_body += 'void NrtSystemTask1(void) {\n'
        cpp_file_body += '\n'
        #add tasks
        for x in range(length):
            if('task1' in tasks['nrt-tasks'][x]):                                                
                cpp_file_body += '   ' + tasks['nrt-tasks'][x]['task1'] + '();\n'   
        cpp_file_body += '}\n'



    
    return 1

def deinit():        
    
    global hpp_file_body
    global cpp_file_body
    
    ##################### Deinir Task ########################
    cpp_file_body += '/**\n'
    cpp_file_body += ' * DeInit tasks\n'
    cpp_file_body += ' * DeInitialize system tasks\n'
    cpp_file_body += ' */\n'
    cpp_file_body += 'void SystemDeInitTasks(void) {\n'    
    cpp_file_body += '  ' + tasks['taskdeinit']['call'] +'();\n' 
    cpp_file_body += '}\n'
    cpp_file_body += '\n'
    cpp_file_body += '\n'
    

if __name__=="__main__":

    # Opening JSON file
    f = open('../../tasks.json',"r")
    # start hpp file
    hpp_file_body += '#ifndef SYSTASKS_HPP_\n'
    hpp_file_body += '#define SYSTASKS_HPP_\n'
    hpp_file_body += '\n'    
    hpp_file_body += '#include "sys_config.hpp"\n'    
    

    jsonContent = f.read()
    tasks = json.loads(jsonContent)
    f.close()
    

    cpp_file_body += '/*\n'
    cpp_file_body += ' * sys_tasks.cpp\n'
    cpp_file_body += ' *\n'
    cpp_file_body += ' *  Created on: Aug 18, 2021\n'
    cpp_file_body += ' *      Author: Rodolfo.Ortega\n'
    cpp_file_body += ' */\n'
    cpp_file_body += '\n'
    cpp_file_body += '#include "system_types.hpp"\n'
    cpp_file_body += '#include "sys_tasks.hpp"\n'
    cpp_file_body += '#include "main_app.hpp"\n'
    cpp_file_body += '#include "sys_timer.hpp"\n'
    cpp_file_body += '#ifdef ENABLE_SYS_TIMER\n'
    cpp_file_body += '#include "sys_logger.hpp"\n'
    cpp_file_body += '#endif //ENABLE_SYS_TIMER\n'
    cpp_file_body += '#include "' + tasks['taskinit']['header'] + '"\n'
    cpp_file_body += '\n'
    cpp_file_body += '\n'
    cpp_file_body += '#ifdef ENABLE_SYS_TIMER\n'
    cpp_file_body += 'struct timespec tmr1, tmr2;\n'    
    cpp_file_body += 'double time_elapsed, max_time_elapsed;\n'
    cpp_file_body += '#endif //ENABLE_SYS_TIMER\n'
    cpp_file_body += '\n'

    init_task(tasks)
    rt_tasks(tasks)        
    nrt_tasks(tasks)
    deinit()


    #end hpp file
    hpp_file_body += '#endif //SYSTASKS_HPP_ \n'
    f_hpp.write(hpp_file_body)
    f_hpp.write('\n')
    f_hpp.close()

    #end cpp file
    f_cpp.write(cpp_file_body)
    f_cpp.write('\n')
    f_cpp.close()
        
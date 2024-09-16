import json
  
f_hpp_cfg = open('sys_config.hpp', 'a')    
hpp_cfg_file_body = ''

def add_sys_cfg(config):
    global hpp_cfg_file_body

    base_time = config["base-time"]
    dgb_logger = config["sys-logger"]["debug"]
    sys_logger = config["sys-logger"]["system"]
    sys_timer = config["sys-timer"]

    if (base_time == "10"):
        hpp_cfg_file_body += '#define     MAIN_CYCLE_nS   10000000.00  // 10ms\n'

    elif (base_time == "20"):
        hpp_cfg_file_body += '#define     MAIN_CYCLE_nS   20000000.00  // 20ms\n'

    elif (base_time == "50"):
        hpp_cfg_file_body += '#define     MAIN_CYCLE_nS   50000000.00  // 50ms\n'

    elif (base_time == "100"):
        hpp_cfg_file_body += '#define     MAIN_CYCLE_nS   100000000.00  // 100ms\n'

    else:
        print("invalid configuration for base-time.")
        print("valid values are: 10, 20, 50, 100")

    hpp_cfg_file_body += '\n' 

    if (dgb_logger == "on"):
        hpp_cfg_file_body += '#define  ENABLE_DEBUG_LOGGER\n'
    elif (dgb_logger == "off"):
         hpp_cfg_file_body += '\n' 
    else:
        print("invalid value for sys-logger->debug")
        print("valid values are: on, off")
    
    if (sys_logger == "on"):
        hpp_cfg_file_body += '#define  ENABLE_SYS_LOGGER\n'
    elif (sys_logger == "off"):
         hpp_cfg_file_body += '\n' 
    else:
        print("invalid value for sys-logger->system")
        print("valid values are: on, off")

    if (sys_timer == "on"):
        hpp_cfg_file_body += '#define  ENABLE_SYS_TIMER\n'
    elif (sys_timer == "off"):
         hpp_cfg_file_body += '\n' 
    else:
        print("invalid value for sys-timer")
        print("valid values are: on, off")
        

if __name__=="__main__":
    # Opening JSON file
    f1 = open('../../sys_config.json',"r")
    #read json data
    jsonContent = f1.read()
    config = json.loads(jsonContent)
    #close file
    f1.close()


    # start hpp file
    hpp_cfg_file_body += '#ifndef SYSCFG_HPP_\n'
    hpp_cfg_file_body += '#define SYSCFG_HPP_\n'
    hpp_cfg_file_body += '\n'    

    #add system configuration to header file
    add_sys_cfg(config)

    #end hpp file
    hpp_cfg_file_body += '\n'  
    hpp_cfg_file_body += '#endif //SYSCFG_HPP_ \n'
    f_hpp_cfg.write(hpp_cfg_file_body)
    #f_hpp_cfg.write('\n')
    f_hpp_cfg.close()
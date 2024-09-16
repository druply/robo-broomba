#import library
import pandas as pd


def cxrte(signals):
    length = len(signals_df)
    f = open('cxrte.cpp', 'a')
    
    file_body = '/*\n'
    file_body += ' * cxrte.cpp\n'
    file_body += ' *\n'
    file_body += ' *  Created on: Aug 18, 2021\n'
    file_body += ' *      Author: Rodolfo.Ortega\n'
    file_body += ' */\n'
    file_body += '\n'
    file_body += '#include "cxdtypes.h"\n'
    file_body += '#include "cxrte.hpp"\n'
    file_body += '\n'
        
    for i in range(length):
        if (signals_df['Type'][i] != 'float') and (signals_df['Type'][i] != 'double'):
            file_body += signals_df['Type'][i] + '_t ' + signals_df['Name'][i] + ';\n'
        else:
            file_body += signals_df['Type'][i] + ' ' + signals_df['Name'][i] + ';\n'
    
    file_body += '\n'

    
    for i in range(length):
        if (signals_df['Type'][i] != 'float') and (signals_df['Type'][i] != 'double'):
            file_body += '/**\n'
            file_body += ' * rte read\n'    
            file_body += ' */\n'
            
            file_body += signals_df['Type'][i] + '_t  rte_Read_' + signals_df['Name'][i] + '(void) {\n'
            file_body += '  return ' + signals_df['Name'][i] + ';\n'
            file_body += '}\n'
            file_body += '\n'
            
            file_body += '/**\n'
            file_body += ' * rte write\n'    
            file_body += ' */\n'
            file_body += '\n'
            file_body += 'void  rte_Write_' + signals_df['Name'][i] + '(' + signals_df['Type'][i] + '_t ' + signals_df['Name'][i] + '_local) {\n'
            file_body += '  ' +  signals_df['Name'][i] + ' = ' + signals_df['Name'][i] + '_local;\n'
            file_body += '}\n'
        else:
            
            file_body += '/**\n'
            file_body += ' * rte read\n'    
            file_body += ' */\n'
            
            
            file_body += signals_df['Type'][i] + '  rte_Read_' + signals_df['Name'][i] + '(void) {\n'
            file_body += '  return ' + signals_df['Name'][i] + ';\n'
            file_body += '}\n'            
            file_body += '\n'
            
            file_body += '/**\n'
            file_body += ' * rte write\n'    
            file_body += ' */\n'
            file_body += '\n'
            
            file_body += 'void  rte_Write_' + signals_df['Name'][i] + '(' + signals_df['Type'][i] + ' ' + signals_df['Name'][i] + '_local) {\n'
            file_body += '  ' + signals_df['Name'][i] + ' = ' + signals_df['Name'][i] + '_local;\n'
            file_body += '}\n'
    

        
    f.write(file_body)
    f.close()
    
    f = open('cxrte.hpp', 'a')    
    file_body = '#ifndef CXRTE_INC\n'
    file_body += '#define CXRTE_INC\n'
    file_body += '\n'
    
    for i in range(length):
        if (signals_df['Type'][i] != 'float') and (signals_df['Type'][i] != 'double'):
            file_body += signals_df['Type'][i] + '_t  rte_Read_' + signals_df['Name'][i] + '(void);\n'
            file_body += 'void  rte_Write_' + signals_df['Name'][i] + '(' + signals_df['Type'][i] + '_t ' + signals_df['Name'][i] + '_local);\n'
        else:
            file_body += signals_df['Type'][i] + '  rte_Read_' + signals_df['Name'][i] + '(void);\n'
            file_body += 'void  rte_Write_' + signals_df['Name'][i] + '(' + signals_df['Type'][i] + ' ' + signals_df['Name'][i] + '_local);\n'
    
    file_body += '\n'
    file_body += '#endif //CXRTE_INC\n'
    f.write(file_body)
    f.close()
     

if __name__=="__main__":
    # open message csv file
    signals_df = pd.read_csv('rte_signals.csv')
    
    cxrte(signals_df)
    

'''
Author: LeiJiulong
Date: 2025-01-17 08:55:21
LastEditors: LeiJiulong && lei15557570906@outlook.com
LastEditTime: 2025-01-17 10:56:15
Description: 自用，用于格式化数据
'''


import glob
import sys
import time
import datetime


'''
处理时间，将其转为微妙时间戳
'''
def date_to_timestamp(date_formate_src: str, date_format = '%Y%m%d %H:%M:%S.%f') -> str:
    # '%Y-%m-%d %H:%M:%S.%f'
    # s = time.strptime(date_formate_src, date_format)
    # s = datetime.datetime.strptime(date_formate_src, date_format)
    # print(date_formate_src ," ", s, " ", s.timestamp())
    return str(datetime.datetime.strptime(date_formate_src, date_format).timestamp())



'''
date_str default format like 20241223
'''
def csv_write(file_source_path:str, file_dist_path:str, date_str:str = "20241223"):
    with open(file_source_path,'r') as sfp, open(file_dist_path, 'w') as dfp:
        line_nun = 0
        while True:    
            line = sfp.readline(-1)

            if not line:
                break
            if line_nun > 0:

                line_nun += 1

                line_split = line.split(',')[1:]
                date_not_format = date_str + " " + line_split[0]
                try:
                    line_split[0] = date_to_timestamp(date_not_format)
                except Exception as e:
                    print(e)
                    print("error in lin %s"%line_nun, "source file is %s"%file_source_path)
                    exit(-1)
                out_line = ",".join(line_split)
                dfp.write(out_line)
            else:
                line_nun += 1
                line_split = line.split(',')[1:]
                out_line = ",".join(line_split)
                dfp.write(out_line)
            
    

def data_path_input(csv_path:str, dest_dir:str=""):
    # 如果输出路径为空则在源文件目录下生成
    if(dest_dir == ""):
        dir_split_str = csv_path.split('/')

        target_name = dir_split_str[-1].split('_')[0] + ".csv"
        # 输出路径
        out_put_path = ''
        for ele in dir_split_str[:-1]:
                out_put_path  = out_put_path + ele +'/'
        out_put_path += target_name
        csv_write(csv_path, out_put_path)
    else:
        pass

if __name__ == "__main__":
    data_dir_path = '.';
    print(sys.argv[0])
    if(len(sys.argv)>1):
        print("get data dir path: ", sys.argv[1])
        data_dir_path = sys.argv[1]
    else:
        print("get data dir path: ", data_dir_path)
    # 获取所有csv地址的列表
    csv_list = glob.glob(data_dir_path+"/*data.csv")
    for ele in csv_list:
        data_path_input(ele)
    

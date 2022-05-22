#文件存储
 >活动相关的本地文件
 * 1.学生个人活动信息放在identity_model下的activity_course_table文件夹中,对于id为x的学生，其所有活动信息存储在该文件夹下的x_activity_table.txt中
 * 2.班级活动信息放在identity_model下的group_set文件夹中,对于id为x的班级，其所有班级活动信息存储在该文件夹下的x_group.txt中
 >课程相关的本地文件
 * 1.对于id为x的学生，在identity_model下的x_activity_table.txt中存储有基本的课程信息，通过这个文件学生可以生产课程表
 * 2.对于id为y的课程，在course_model下的course_set文件夹下面的y_course.txt中存储有该课程的全部公共信息
 >作业相关的本地文件
 * 1.对于学生id x,其在任课教师id为y的课程id为z的课程的第i次作业的全部信息存储在identity_model下的homework_set/y_teacher/z_course/i_times/
 x_stu文件夹中
 * 2.压缩后的作业在该文件夹下的zip.txt,码表在unzip.txt,解码后作业在hw.txt,作业分数与提交状态在info.txt中
> 资料相关的本地文件
* 待定
>用户信息相关的本地文件
* 1.identity_model下的admin_info.txt中存储管理员id,密码
* 2.identity_model下的stu_info.txt中存储学生id,密码,姓名,班级id
* 3.identity_model下的teacher_info.txt中存储老师id,密码,姓名
#模块说明
##course_model
>数据结构说明和数据字典
* 1.struct single_course
存储一堂课的单元
* 2.struct material
存储一份电子资料的单元（包含权重信息）
* 3.struct hw
存储一份作业信息的单元（包含成绩信息）
* 4.vector<int> order_hws
以成绩为关键字进行快速排序时，存放排序结果的下标
* 5.vector<int> order_materials
以权重为关键字进行快速排序时，存放排序结果的下标
>实现的功能
 * 1.提交课程作业    
 *  2.提交课程资料                            
* 3.下载课程资料    
* 4.作业名称查询   
 *   5.作业成绩排序    
 * 6.资料名称查询   
  * 7.资料权重排序
>算法
* 以下标转换为基础的快速排序，既可以节省空间，又提高效率
>与其他模块交互
* 学生用户可以在个人主页中通过课程表选定课程或者通过搜索来创建课程类实例并进入课程界面实现课程提供的各种功能
  
##identiy_model
####学生用户
>数据结构说明和数据字典
* 1.map<string, string> name_to_id
在找到正确的名字后通过名字找到对应的课程下标，通过下标可以读取课程文件创建课程类
* 2.map<int, pair<string, string> > time_to_place
在找到合理的时间（大于输入时间的最新上课开始时间）后必须通过时间查找到对应的地名（校区+建筑），这样学生可以实现通过时间进行导航
* 3.string my_course_table[6][12]
存储学生课程表
* 4.Node t1[1000],Node t2[1000]
分别是用来存储课程时间和活动时间的二叉搜索树
* 5. map<string, vector<single_activity> > name_to_activity
在找到正确的名字后通过名字找到对应的活动
* 6.    map<int, vector<single_activity> > time_to_activity
在找到正确的时间后通过时间找到对应的活动
* 7.struct single_activity
存储活动信息的单元
>算法
* 利用二叉搜索树进行数据的查找，复杂度为O(lnx)
* 利用两区间中点的距离的绝对值和两区间总长度之间的大小关系方便的检测冲突
* dijstra算法进行最短路计算
> 实现的功能
* 1.课程名称查询  
                                      
 *   2.课表课程查询    
                                       
 *  3.课程时间查询    
                                       
*   4.活动名称查询    
                                       
 *   5.进入活动菜单（进入后可以对个人活动增删改)    
                                      
*    6.活动时间查询    
                                       
 *    7.进行路径导航 
 > 与其他模块交互
 * 1.可以通过课表查询或者课程名称查询创建course实例，完成学生所需要的与课程有关的功能 
 * 2.与活动相关的功能都在本模块内部实现
 * 3.通过路径导航功能可以创建guide实例，实现学生的导航需求

 #### 管理员用户
> 数据结构说明和数据字典
* 1.struct single_course_a
一堂课
* 2.whole_course_a
一门课
* 3.single_activity_a
一次活动
> 实现的功能
* 1.班级活动菜单（对班级活动进行增加和删除）
* 2.发布新的课程
* 3.修改原有课程
> 与其他模块交互
* 管理员对文件的修改将会影响到其他用户在之后读取各种数据的情况


 
     
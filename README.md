#### 2022 Spring BUPT Data Structure Course Design

__Under construction now.__

Team Member:
- [@livrth](https://github.com/livrth)
- [@likely-dog](https://github.com/likely-dog)
- [@guanshuidong](https://github.com/guanshuidong)


4/19 TODO:
- [x] 学生用户注册等功能
- [x] 初始分身份登录功能
- [x] 学生提交作业功能实现/压缩算法实现
- [x] 学生和管理员操作菜单及子菜单
- [x] 学生课内信息管理和查询的基本函数实现

5/1 TODO:
- [x] 取消 `campus_model` 合并入 `navigation_model`
- [x] 学生导航菜单

5/22 TODO:
- [ ] 学生可选4种不同方法导航
    - 步行最短距离策略(同校区内,不考虑拥挤度)
    - 步行最短时间策略(同校区内,考虑拥挤度)
    - 自行车道的最短时间策略(自行车速度倍率设置)
- [x] 跨校区交通规划
    - 根据课表自动识别校区
    - 输出校区间路径规划方案(定点班车/公共汽车)
    - 先抵达校区再规划校园路径
- [x] 系统计时器
    - 导航貌似不依赖,只需要课表时间/班车时间即可


Final TODO:

- [ ] 系统计时器(支持快进/暂停)
- [ ] 闹钟(需要获取到当前时间/多线程)
- [ ] 日志功能
    - 在所有菜单操作进行日志记录
    - 时间为系统时间不需要模拟
- [ ] 最终项目文档
<template>
  <div>
    <el-tabs v-model="activeName" type="card">
    <el-tab-pane label="部门管理" name="DepManage"><DepManage/></el-tab-pane>
    <el-tab-pane label="职位管理" name="PosManage"> <PosManage/> </el-tab-pane>
    <el-tab-pane label="职称管理" name="JobLevelManage"> <JobLevelManage/> </el-tab-pane>
    <el-tab-pane label="奖惩规则" name="EcManage"><EcManage/></el-tab-pane>
    <el-tab-pane label="权限组" name="PermissionManage"><PermissionManage/></el-tab-pane>
  </el-tabs>  
  </div>
</template>

<script>
import JobLevelManage from '../../components/sys/basic/JobLevelManage.vue'
import DepManage from '../../components/sys/basic/DepManage.vue'
import EcManage from '../../components/sys/basic/EcManage.vue'
import PermissionManage from '../../components/sys/basic/PermissManage.vue'
import PosManage from '../../components/sys/basic/PosManage.vue'

export default {
  name: 'SysBasic',
  data() {
    return {
      activeName: 'DepManage'
    }
  },

  components: {
    DepManage,
    JobLevelManage,
    EcManage,
    PermissionManage,
    PosManage
  }
}
</script>

<style scoped>

</style>
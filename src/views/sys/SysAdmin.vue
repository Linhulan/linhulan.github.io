<template>
  <div>
    <div style="display:flex; justify-content:center">
      <el-input
        placeholder="通过用户名搜索"
        prefix-icon="el-icon-search"
        style="width: 400px; margin-right: 10px"
        v-model="keywords"
        @keydown.enter.native="doSearch"
      >
      </el-input>
      <el-button type="primary" @click="doSearch">搜索</el-button>
    </div>

    <div class="adminCard-container">
      <el-card class="admin-card" v-for="(admin, index) in admins" :key="'admin'+admin.id">
        <div slot="header" class="clearfix">
          <span>{{admin.name}}</span>
          <el-button 
              style="float: right; padding: 3px 0; color:red" 
              type="text"
              icon="el-icon-delete"
              @click="doDeleteAdmin(admin)"
            ></el-button
          >
        </div>
        <div>
          <div class="img-container">
            <!-- src="@/assets/userFace1.jpeg"
              src="http://localhost:8080/img/userFace1.58c7a34d.jpeg" -->
            <img 
              :src="`http://localhost:8082/${admin.userFace}`"
              :alt="admin.name" 
              :title="admin.name"
              class="userFace-class">
          </div>
        </div>
        <div class="userInfo-container">
          <div>用户名: {{admin.name}}</div>
          <div>手机号码: {{admin.phone}}</div>
          <div>电话号码: {{admin.telephone}}</div>
          <div>地址: {{admin.address}}</div>
          <div>用户状态:
            <el-switch
              v-model="admin.enabled"
              @change="enabledChange(admin)"
              active-color="#13ce66"
              inactive-color="#ff4949"
              active-text="启用"
              inactive-text="禁用">
            </el-switch>
          </div>
          <div>用户角色：
            <el-tag
              style="margin:6px 6px 0px 0px"
              type="success"
              v-for="(role, indexj) in admin.roles" 
              :key="'role'+role.id">{{role.nameZh}}
              </el-tag>
              
               <el-popover
                placement="right"
                title="角色列表"
                width="200"
                @show="showPop(admin)"
                @hide="hidePop(admin)"
                trigger="click">
                <el-select v-model="selectedRoles" multiple placeholder="请选择">
                  <el-option
                    v-for="(item, indexk) in allRoles"
                    :key="'option'+item.id"
                    :label="item.nameZh"
                    :value="item.id">
                  </el-option>
                </el-select>
                <el-button slot="reference" type="text" icon="el-icon-plus" ></el-button>
              </el-popover>
          </div>
        </div>

      </el-card>
    </div>
  </div>
</template>

<script>
export default {
  name: "SysAdmin",
  data() {
    return {
      // admin: {
      //   name: '',
      //   username: '',
      // },
      admins: [],
      allRoles: [],
      selectedRoles:[],
      keywords: ''
    }
  },
  methods: {
    hidePop(admin){
      let roles1 = [];
      let roles2 = [];
      let dirty = false;
      if ( admin.roles.length != this.selectedRoles.length ){
        dirty = true;
      } else {
        Object.assign(roles1, admin.roles);
        Object.assign(roles2, this.selectedRoles);
        let j = 0;
        for ( let i=0; i<roles1.length; i++ ){
          for ( j=0; j<roles2.length; j++ ){
            if ( roles1[i].id == roles2[j] ){
              break;
            }
          }
          if ( j>=roles2.length ) {
            dirty = true;
            break;
          }
        }
      }

      if ( !dirty ) return ;
      let url = '/system/admin/roles/?adminId='+admin.id;
      this.selectedRoles.forEach(rid => {
        url += '&rids='+rid;
      })
      // console.log(url)
      this.putRequest(url).then(resp => {
        if (resp){
          this.initAdmins();
        }
      })
    },
    showPop(admin){
      // this.initAllRoles();
      this.selectedRoles = [];    //只需要role.id  所以不能直接赋值
      admin.roles.forEach(r => {
        this.selectedRoles.push(r.id);
      });
    },
    doSearch() {
      this.initAdmins();
    },
    doDeleteAdmin(admin){
      this.$confirm(
        "此操作将永久删除[" + admin.name + "]操作员, 是否继续?",
        "提示",
        {
          confirmButtonText: "确定",
          cancelButtonText: "取消",
          type: "warning",
        }
      )
        .then(() => {
          this.deleteRequest('/system/admin/'+admin.id).then((resp) => {
              if (resp) {
                this.initAdmins();
              }
            });
        })
        .catch(() => {
          this.$message({
            type: "info",
            message: "已取消删除",
          });
        });
    },
    enabledChange(admin){
      this.putRequest('/system/admin/', admin).then(resp=>{
        if (resp){
          this.initAdmins();
        }
      })
    },
    initAdmins() {
      this.getRequest("/system/admin/?keywords=" + this.keywords).then((resp) => {
        if (resp) {
          this.admins = resp;
        }
      });
    },
    initAllRoles() {
      this.getRequest("/system/basic/permission/").then((resp) => {
        if (resp) {
          this.allRoles = resp;
        }
      });
    },
  },
  mounted() {
    this.initAdmins();
    this.initAllRoles();
  },
};
</script>

<style scoped>
.admin-card {
  width: 350px;
  margin: 10px 6px;
}
.adminCard-container {
  display: flex;
  flex-wrap: wrap;
}
.userFace-class {
  width: 72px;
  height: 72px;
  border-radius: 72px;
}
.img-container {
  width: 100%;
  display: flex;
  justify-content: center;
}
.userInfo-container {
  font-size: 12px;
  font-weight: bold;
  line-height: 25px;
}
</style>
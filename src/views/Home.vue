<template>
  <el-container>
    <el-header class="homeHeader">
      <div class="headerLeft">
        <img src="../assets/WZUTLogo.png" alt="">
      </div>
      
      <!-- <div class="title"> </div> -->
      <div>
        <el-button @click="goChat" icon="el-icon-chat-dot-round" type="text" size="medium" style="margin-right: 8px"></el-button>
        <el-dropdown class="userInfo" @command="commandHandler">
          <span class="el-dropdown-link">
            {{user.name}}<i><img :src="`http://localhost:8082/${user.userFace}`" alt=""></i>
          </span>
          <el-dropdown-menu slot="dropdown">
            <el-dropdown-item command="userInfo" >个人中心</el-dropdown-item>
            <el-dropdown-item command="setting" >设置</el-dropdown-item>
            <el-dropdown-item command="logout" >注销</el-dropdown-item>
          </el-dropdown-menu>
        </el-dropdown>
      </div>
    </el-header>
    <el-container>
      <el-aside width="200px">
        <el-menu router unique-opened>
          <el-submenu
            :index="'' + index"
            v-for="(item, index) in routes"
            :key="index"
            v-if="!item.hidden"
          >
            <template slot="title">
              <i
                :class="item.iconCls"
                style="color: #a3c6fd; margin-right: 5px"
              ></i>
              <span>{{ item.name }}</span>
            </template>

            <el-menu-item
              v-for="(children, indexj) in item.children"
              :key="indexj"
              :index="children.path"
            >
              {{ children.name }}
            </el-menu-item>
          </el-submenu>
        </el-menu>
      </el-aside>

      <el-main>
        <el-breadcrumb separator-class="el-icon-arrow-right"
                       v-if="this.$router.currentRoute.path != '/home'">
          <el-breadcrumb-item :to="{ path: '/home' }">首页</el-breadcrumb-item>
          <el-breadcrumb-item>{{this.$router.currentRoute.name}}</el-breadcrumb-item>
        </el-breadcrumb>
        <div v-else>
          欢迎来到温理办公系统
        </div>
        <router-view class="homeRouterView" />
      </el-main>
    </el-container>
  </el-container>
</template>

<script>

export default {
  name: "Home",
  data() {
    return {
      // user:'',
      client:null,
    };
  },
  methods: {
    goChat(){
      this.$router.push('/chat')
    },
    commandHandler(command){
      switch (command){
        case 'logout': 
          this.$confirm('此操作将注销用户, 是否继续?', '提示', {
          confirmButtonText: '确定',
          cancelButtonText: '取消',
          type: 'warning'
          }).then(() => {
            // let user = JSON.parse(window.sessionStorage.getItem('user'))
            // console.log(user.id)
            this.postRequest('/logout/?adminId='+user.id);
            window.sessionStorage.removeItem('tokenStr');
            window.sessionStorage.removeItem('user');
            this.$store.commit('initRoutes', []);
            this.$router.replace('/');
            return ;
          }).catch(() => {
            this.$message({
              type: 'info',
              message: '已取消'
            });          
          });

        case 'userInfo':
          this.$router.push('/userInfo');
          return ;
        case 'setting':
          return ;
      }

    },
    loadUser(){
      this.user = JSON.parse(window.sessionStorage.getItem('user'));
      console.log("user:")
      console.log(this.user)
    }
  },
  computed: {
    routes() {
      // console.log(this.$store.state);
      return this.$store.state.routes;
    },
    user(){
      return this.$store.state.currentAdmin;
    }
  },
  mounted(){
    this.loadUser()
  }
};
</script>


<style scoped>
.el-aside {
  overflow: hidden;
}
.homeHeader {
  /* background: #409eff; */
  /* background-image: linear-gradient(120deg,#c2e9fb 0%, #a1c4fd 100%); */
  /* background-image: linear-gradient(120deg, #a1c4fd 0%, #c2e9fb 100%); */
  background-image: linear-gradient(to right, #4facfe 0%, #c2e9fb 100%);
  display: flex;
  align-items: center;
  justify-content: space-between;
  padding: 0px 15px;
  box-sizing: border-box;
}
/* .homeHeader .title {
  flex: 1.5;
  font-size: 30px;
  font-family: 楷体;
  color: white;
  background: "../assets/WZUTIcon.png";
} */
.homeHeader .userInfo {
  margin: 0px 10px 0px 0px;
}
.el-dropdown-link img{
  width: 48px;
  height: 48px;
  border-radius: 24px;
  margin-left: 10px;
}
.headerLeft {
  flex: -1;
}
.headerLeft img {
  height: 60px;
}
.homeRouterView{
  margin-top: 10px;
}
</style>

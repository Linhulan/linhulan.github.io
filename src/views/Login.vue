<template>
  <div class="LoginBox">
    <el-form
      :model="loginForm"
      v-loading="loading"
      element-loading-text="拼命加载中..."
      element-loading-spinner="el-icon-loading"
      element-loading-background="rgba(0, 0, 0, 0.8)"
      ref="loginForm"
      :rules="rules"
      class="loginContainer"
    >
      <h3 class="loginTitle">系统登录</h3>
      <el-form-item label="" prop="username">
        <el-input
          @keydown.enter.native="submitLogin()"
          prefix-icon="fa fa-user fa-fw"
          v-model="loginForm.username"
          type="text"
          auto-complete="false"
          placeholder="请输入用户名" 
        >
        </el-input>
      </el-form-item>

      <el-form-item label="" prop="password">
        
        <el-input
          @keydown.enter.native="submitLogin()"
          prefix-icon="fa fa-key fa-fw"
          v-model="loginForm.password"
          type="password"
          auto-complete="false"
          placeholder="请输入密码"
        >
        </el-input>
      </el-form-item>

      <el-form-item prop="code">
        <el-input
          @keydown.enter.native="submitLogin()"
          prefix-icon="fa fa-vcard"
          class="loginCaptcha"
          v-model="loginForm.code"
          type="text"
          auto-complete="false"
          placeholder="点击图片切换验证码"
        >
        </el-input>
        <!-- 验证码 -->
        <img :src="captchaUrl" @click="updateCaptcha"/>
      </el-form-item>

      <el-checkbox
        class="loginRemember"
        v-model="checked"
        @change="rememberMe()"
        >记住我</el-checkbox
      >

      <el-button
        class="loginButton"
        type="primary"
        style="width: 100%"
        @click="submitLogin()"
        >登录</el-button
      >

    </el-form>
  </div>
</template>

<script>

export default {
  name: "Login",
  data() {
    return {
      captchaUrl: "/captcha?" + new Date(),   //刷新验证码
      checked: true,
      loading: false,
      loginForm: {
        username: "admin",
        password: "123",
        code: "",
      },
      rules: {
        username: [{ required: true, message: "请输入用户名", trigger: "blur" }],
        password: [{ required: true, message: "请输入密码", trigger: "blur" }],
        code: [{ required: true, message: "请输入验证码", trigger: "blur" }],
      },
    };
  },
  methods: {
    rememberMe() {},

    submitLogin() {
      this.$refs.loginForm.validate((valid) => {
        if (valid) {
          this.loading = true;
          this.postRequest('/login', this.loginForm)
              .then(resp => {
                // alert(JSON.stringify(resp));
                if ( resp ){
                  this.loading = false;
                  // 存储用户token
                  const tonkenStr = resp.obj.tokenHead + resp.obj.token;
                  window.sessionStorage.setItem('tokenStr', tonkenStr);
                  // 跳转首页
                  var path = this.$route.query.redirect;
                  this.$router.replace( (path=='/' || path==undefined) ? '/home':path )
                  // this.$router.push('/home');
                }
              })
        } else {
          this.$message.error('请输入所有字段!');
          return false;
        }
      });
    },

    updateCaptcha(){
      this.captchaUrl = '/captcha?'+new Date();
    },
  },
};
</script>

<style>
.LoginBox{
  margin: 0px;
  padding: 0px;
  width: 100%;
  height: 800px;
  
  background-repeat: no-repeat;
}
.loginContainer {
  border-radius: 15px;
  background-clip: padding-box;
  margin: 180px auto;
  width: 350px;
  padding: 15px 35px 25px 35px;
  background: #fff;
  border: 1px solid #eaeaea;
  box-shadow: 0 0 25px #cac6c6;
  
}
.loginTitle {
  text-align: center;
  margin: 10px auto;
}
.loginRemember {
  text-align: left;
  margin: 0px 0px 15px 0px;
}
.loginCaptcha {
  width: 250px;
  margin-right: 5px;
}

.el-form-item__content {
  display: flex;
  align-items: center;
}

</style>
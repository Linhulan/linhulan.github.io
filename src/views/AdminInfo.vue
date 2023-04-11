<template>
  <div>
    <el-card class="box-card adminInfo-card" style="width: 400px">
      <div slot="header" class="clearfix">
        <span>{{ admin.name }}</span>
      </div>
      <div style="display: flex; justify-content: center">
        <el-upload
          action="/admin/userFace"
          :headers="headers"
          :data="admin"
          :show-file-list="false"
          :on-success="onSuccess"
        >
          <img
            title="点击修改用户头像"
            :src="`http://localhost:8082/${admin.userFace}`"
            style="height: 100px; width: 100px; border-radius: 50px"
            alt=""
          />
        </el-upload>
      </div>
      <div>
        电话号码：
        <el-tag>{{ admin.telephone }}</el-tag>
      </div>
      <div>
        手机号码：
        <el-tag>{{ admin.phone }}</el-tag>
      </div>
      <div>
        居住地址：
        <el-tag>{{ admin.address }}</el-tag>
      </div>
      <div>
        用户标签：
        <el-tag
          style="margin-right: 5px"
          type="success"
          v-for="(r, index) in admin.roles"
          :key="index"
        >
          {{ r.nameZh }}
        </el-tag>
      </div>
      <div
        style="display: flex; justify-content: space-around; margin-top: 10px"
      >
        <el-button type="primary" @click="showUpdateAdminInfoView"
          >修改信息</el-button
        >
        <el-button type="danger" @click="showUpdatePasswordView"
          >修改密码</el-button
        >
      </div>
    </el-card>
    <el-dialog title="编辑用户信息" :visible.sync="dialogVisible" width="30%">
      <div>
        <table>
          <tr>
            <td>用户昵称：</td>
            <td>
              <el-input v-model="admin2.name"></el-input>
            </td>
          </tr>
          <tr>
            <td>电话号码：</td>
            <td>
              <el-input v-model="admin2.telephone"></el-input>
            </td>
          </tr>
          <tr>
            <td>手机号码：</td>
            <td>
              <el-input v-model="admin2.phone"></el-input>
            </td>
          </tr>
          <tr>
            <td>用户地址：</td>
            <td>
              <el-input v-model="admin2.address"></el-input>
            </td>
          </tr>
        </table>
      </div>
      <span slot="footer" class="dialog-footer">
        <el-button @click="dialogVisible = false">取 消</el-button>
        <el-button type="primary" @click="updateAdminInfo">确 定</el-button>
      </span>
    </el-dialog>
  </div>
</template>

<script>
export default {
  name: "AdminInfo",
  data() {
    return {
      headers: {
        Authorization: window.sessionStorage.getItem('tokenStr'),

      },
      admin: null,
      admin2: null,
      dialogVisible: false,
    };
  },
  methods: {
    onSuccess(){
      this.initAdmin();
    },
    showUpdatePasswordView() {},
    showUpdateAdminInfoView() {
      this.dialogVisible = true;
    },
    updateAdminInfo() {
      this.putRequest("/admin/info", this.admin2).then((resp) => {
        if (resp) {
          this.dialogVisible = false;
          this.initAdmin();
        }
      });
    },
    initAdmin() {
      this.getRequest("/admin/info").then((resp) => {
        if (resp) {
          this.admin = resp;
          this.admin2 = Object.assign({}, this.admin);
          window.sessionStorage.setItem("user", JSON.stringify(resp));
          this.$store.commit("INIT_ADMIN", resp);
        }
      });
    },
  },
  mounted() {
    this.initAdmin();
  },
};
</script>

<style scoped>
.adminInfo-card .el-tag {
  margin: 4px 0px;
}
</style>
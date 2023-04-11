<template>
  <div>
    <div class="permissionManageTool">
      <el-input size="small" placeholder="请输入角色英文名" v-model="role.name">
        <template slot="prepend">ROLE_</template>
      </el-input>
      <el-input
        size="small"
        v-model="role.nameZh"
        placeholder="请输入角色中文名"
        @keydown.enter.native="doAddRole"
      ></el-input>
      <el-button
        size="small"
        type="primary"
        @click="doAddRole"
        icon="el-icon-plus"
        >添加</el-button
      >
    </div>

    <div style="width: 70%">
      <el-collapse v-model="activeName" accordion @change="change">
        <el-collapse-item
          :title="r.nameZh"
          :name="r.id + ',' + index"
          v-for="(r, index) in roles"
          :key="index"
        >
          <el-card class="box-card">
            <div slot="header" class="clearfix">
              <span>可访问资源</span>
              <el-button
                style="float: right; padding: 3px 0; color: #ff0000"
                type="text"
                icon="el-icon-delete"
                @click="doDeleteRole(r)"
              ></el-button>
            </div>
            <div>
              <el-tree
                ref="tree"
                show-checkbox
                :data="allMenus"
                :props="defaultProps"
                :default-checked-keys="selectedMenus"
                node-key="id"
              ></el-tree>
              <div
                style="
                  margin-top: 6px;
                  display: flex;
                  justify-content: flex-end;
                "
              >
                <el-button size="mini" type="info" @click="cancelUpdate"
                  >取消修改</el-button
                >
                <el-button
                  size="mini"
                  type="primary"
                  @click="doUpdate(r.id, index)"
                  >确认修改</el-button
                >
              </div>
            </div>
          </el-card>
        </el-collapse-item>
      </el-collapse>
    </div>
  </div>
</template>

<script>
export default {
  name: "PermissManage",
  data() {
    return {
      activeName: -1,
      role: {
        name: "",
        nameZh: "",
      },
      roles: [],
      allMenus: [],
      defaultProps: {
        children: "children",
        label: "name",
      },
      selectedMenus: [],
    };
  },
  methods: {
    initRoles() {
      this.getRequest("/system/basic/permission/").then((resp) => {
        if (resp) {
          this.roles = resp;
        }
      });
    },
    initMenus() {
      this.getRequest("/system/basic/permission/menu").then((resp) => {
        if (resp) {
          this.allMenus = resp;
        }
      });
    },
    initSelectedMenus(rid, index) {
      return new Promise((resolve) => {
        this.getRequest("/system/basic/permission/mid/" + rid).then((resp) => {
          if (resp) {
            this.$refs.tree[index].setCheckedKeys(resp);
            // console.log(this.$refs.tree)
            // this.$refs.tree.setCheckedKeys([3]);
          }
        });
      });
    },
    doAddRole() {
      if (this.role.name && this.role.nameZh) {
        this.postRequest("/system/basic/permission/role", this.role).then(
          (resp) => {
            if (resp) {
              this.role.name = this.role.nameZh = "";
              this.initRoles();
              // this.activeName = -1;
            }
          }
        );
      } else {
        this.$message.error("所有字段不能为空！");
      }
    },
    async change(activeName) {
      // console.log(activeName);
      if (activeName) {
        let [rid, index] = activeName.split(',');
        this.initMenus();
        await this.initSelectedMenus(rid, index);
      }
    },
    doUpdate(rid, index) {
      let tree = this.$refs.tree[index];
      let selectedKeys = tree.getCheckedKeys(true);
      let url = "/system/basic/permission/?rid=" + rid;
      selectedKeys.forEach((key) => {
        url = url + "&mids=" + key;
      });
      // console.log(url)
      this.putRequest(url).then((resp) => {
        if (resp) {
          this.activeName = -1;
        }
      });
    },
    cancelUpdate() {
      this.activeName = -1;
    },
    doDeleteRole(r) {
      this.$confirm(
        "此操作将永久删除[" + r.nameZh + "]角色, 是否继续?",
        "提示",
        {
          confirmButtonText: "确定",
          cancelButtonText: "取消",
          type: "warning",
        }
      )
        .then(() => {
          this.deleteRequest("/system/basic/permission/role/" + r.id).then((resp) => {
              if (resp) {
                this.initRoles();
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
  },
  mounted() {
    this.initRoles();
    // this.initMenus();
  },
};
</script>

<style scoped>
.permissionManageTool {
  display: flex;
  justify-content: flex-start;
}
.permissionManageTool .el-input {
  width: 300px;
  margin-right: 6px;
}
</style>
<template>
  <div>
    <div>
      <el-input
        v-model="jobLevel.name"
        placeholder="添加职称等级"
        prefix-icon="el-icon-plus"
        style="width: 300px"
        size="small"
      ></el-input>
      <el-select size="small" v-model="jobLevel.titleLevel" placeholder="职称等级" style="margin: 0px 6px">
        <el-option
          v-for="item in titleLevels"
          :key="item"
          :label="item"
          :value="item">
        </el-option>
      </el-select>

      <el-button size="small" type="primary" @click="addJobLevel" icon="el-icon-plus">添加</el-button>
    </div>

    <!-- <div>
      <el-table
        :data="jobLevels"
        stripe
        border
        style="width: 70%"
        size="small">
        <el-table-column
          prop="id"
          label="编号"
          width="55">
        </el-table-column>
        <el-table-column
          prop="name"
          label="职称姓名"
          width="150">
        </el-table-column>
        <el-table-column
          prop="titleLevel"
          label="职称等级"
          width="150">
        </el-table-column>
        <el-table-column
          prop="createDate"
          label="创建日期"
          width="150">
        </el-table-column>
        <el-table-column
          prop="enabled"
          label="是否启用"
          width="150">
        </el-table-column>
        <el-table-column
          label="操作">
          <template slot-scope="scope">
            <el-button size="small">编辑</el-button>
            <el-button size="small" type="danger">删除</el-button>
          </template>
        </el-table-column>
      </el-table>
    </div> -->

    <div style="margin-top:10px">
      <el-table
        :data="jobLevels"
        style="width: 70%"
        stripe
        border
        size="small"
        @selection-change="handleSelectionChange"
      >
        <el-table-column type="selection" width="55"> </el-table-column>
        <el-table-column prop="id" label="编号" width="55"> </el-table-column>
        <el-table-column prop="name" label="职称名称" width="120">
        </el-table-column>
        <el-table-column prop="titileLevel" label="职称等级" width="120">
          <template slot-scope="scope">
            <div slot="reference" class="name-wrapper">
              <el-tag size="medium">{{ scope.row.titleLevel }}</el-tag>
            </div>
          </template>
        </el-table-column>
        <el-table-column prop="createDate" label="创建时间" width="120">
        </el-table-column>
        <el-table-column prop="enabled" label="是否启用" width="120">
          <template slot-scope="scope">
            <el-tag v-if="scope.row.enabled" type="success">已启用</el-tag>
            <el-tag v-else type="danger">未启用</el-tag>
          </template>
        </el-table-column>
        <el-table-column label="操作">
          <template slot-scope="scope">
            <el-button
              size="small"
              @click="showEditView(scope.$index, scope.row)"
              >编辑</el-button
            >
            <el-button
              size="small"
              type="danger"
              @click="handleDelete(scope.$index, scope.row)"
              >删除</el-button
            >
          </template>
        </el-table-column>
      </el-table>
    </div>
    <el-button
      type="danger"
      size="small"
      style="margin-top: 8px"
      :disabled="this.multipleSelection.length == 0"
      @click="deleteMany"
      >批量删除</el-button
    >
    <el-dialog title="编辑职称" :visible.sync="dialogVisible" width="30%">
      <table>
        <tr>
          <td>
            <el-tag>职称名称</el-tag>
          </td>
          <td>
            <el-input
              v-model="updateJobLevel.name"
              class="updateJobLevel"
              size="small"
            ></el-input>
          </td>
        </tr>
        <tr>
          <td>
            <el-tag>职称等级</el-tag>
          </td>
          <td>
            <el-select size="small" v-model="updateJobLevel.titleLevel" placeholder="职称等级" style="margin: 0px 6px">
              <el-option
                v-for="item in titleLevels"
                :key="item"
                :label="item"
                :value="item">
              </el-option>
            </el-select>
          </td>
        </tr>
        
        <tr>
          <td>
            <el-tag>是否启用</el-tag>
          </td>
          <td>
            <el-switch
              style="margin:0px 0px 0px 6px"
              v-model="updateJobLevel.enabled"
              active-color="#13ce66"
              inactive-color="#ff4949"
              active-text="已启用"
              inactive-text="未启用">
            </el-switch>
          </td>
        </tr>
        
      </table>
      <span slot="footer" class="dialog-footer">
        <el-button size="small" @click="dialogVisible = false">取 消</el-button>
        <el-button size="small" type="primary" @click="doUpdate"
          >确 定</el-button
        >
      </span>
    </el-dialog>
  </div>
</template>

<script>
export default {
  name: "JobLevelManage",
  data() {
    return {
      jobLevel: {
        name: "",
        titleLevel: "",
      },
      updateJobLevel: {
        name: "",
        titleLevel: "",
        enabled: "",
      },
      titleLevels:[
        '正高级',
        '副高级',
        '中级',
        '初级',
        '员级',
      ],
      jobLevels: [],
      dialogVisible: false,
      multipleSelection: [],
    };
  },
  methods: {
    initJobLevels(){
      this.getRequest('/system/basic/joblevel').then(resp=>{
        if ( resp ){
          this.jobLevels = resp;
        }
      })
    },
    addJobLevel() {
      if (this.jobLevel.name && this.jobLevel.titleLevel) {
        this.postRequest("/system/basic/joblevel", this.jobLevel).then((resp) => {
          if (resp) {
            this.initJobLevels();
            this.jobLevel.name = '';
            this.jobLevel.titleLevel = '';
          }
        });
      } else {
        this.$message.error("职称名称和职称等级不能为空！");
      }
    },

    showEditView(index, data) {
      Object.assign(this.updateJobLevel, data); //浅拷贝，防止双向绑定后修改name直接显示在页面上
      this.updateJobLevel.createDate = ""; //后端自动生成，不接受修改
      this.dialogVisible = true;
    },
    doUpdate() {
      this.putRequest("/system/basic/joblevel/", this.updateJobLevel).then((resp) => {
        if (resp) {
          this.dialogVisible = false;
          this.initJobLevels();
        }
      });
    },

    handleDelete(index, data) {
      this.$confirm(
        "此操作将永久删除[" + data.name + "]职称, 是否继续?",
        "提示",
        {
          confirmButtonText: "确定",
          cancelButtonText: "取消",
          type: "warning",
        }
      ).then(() => {
          this.deleteRequest("/system/basic/joblevel/" + data.id).then((resp) => {
            if (resp) {
              this.initJobLevels();
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
    handleSelectionChange(val) {
      this.multipleSelection = val;
    },
    deleteMany(){
      this.$confirm(
        "此操作将永久删除[" + this.multipleSelection.length + "]条职位, 是否继续?",
        "提示",
        {
          confirmButtonText: "确定",
          cancelButtonText: "取消",
          type: "warning",
        }
      )
      .then(() => {
        let ids = '?';
        this.multipleSelection.forEach(item=>{
          ids += 'ids='+item.id+'&';
        });
        this.deleteRequest("/system/basic/joblevel/" + ids).then((resp) => {
          if (resp) {
            this.initJobLevels();
          }
        }).catch(()=>{
            this.$message({
            type: "error",
            message: "参数错误",
          });
        })
      })
      .catch(() => {
        this.$message({
          type: "info",
          message: "已取消删除",
        });
      });
    },
  },
  mounted(){
    this.initJobLevels();
  }
};
</script>

<style scoped>
.updateJobLevel{
  margin: 0px 0px 0px 6px;
}
</style>
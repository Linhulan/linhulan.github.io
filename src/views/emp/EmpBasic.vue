<template>
  <div>
    <header style="display: flex; justify-content: space-between">
      <div>
        <el-input
          style="width: 300px; margin-right: 10px"
          clearable
          :disabled="advancedSearchVisible"
          v-model="empName"
          @keydown.enter.native="initEmps"
          @clear="initEmps"
          prefix-icon="el-icon-search"
          placeholder="请输入员工名搜索"
        >
        </el-input>
        <el-button
          icon="el-icon-search"
          :disabled="advancedSearchVisible"
          type="primary"
          @click="initEmps()"
          >搜索</el-button
        >
        <el-button
          type="primary"
          @click="advancedSearchVisible = !advancedSearchVisible"
        >
          <i
            :class="
              advancedSearchVisible
                ? 'fa fa-angle-double-up'
                : 'fa fa-angle-double-down'
            "
            aria-hidden="true"
          ></i>
          高级搜索
        </el-button>
      </div>
      <!-- header操作按钮 -->
      <div>
        <el-button type="success">
          <i class="fa fa-level-up" aria-hidden="true">导入数据</i>
        </el-button>
        <el-button type="success" @click="exportData">
          <i class="fa fa-level-down" aria-hidden="true">导出数据</i>
        </el-button>
        <el-button type="primary" icon="el-icon-plus" @click="showAddView">
          添加员工
        </el-button>
      </div>
    </header>
    <!-- 高级搜索表单 -->
    <el-collapse-transition>
      <div
        v-show="advancedSearchVisible"
        style="
          border: 1px solid #409eff;
          border-radius: 5px;
          box-sizing: border-box;
          padding: 5px;
          margin: 10px 0px;
        "
      >
        <el-row>
          <el-col :span="5">
            政治面貌:
            <el-select
              v-model="searchValue.politicId"
              size="mini"
              style="width: 130px"
              placeholder="政治面貌"
            >
              <el-option
                v-for="item in politicsStatus"
                :key="item.id"
                :label="item.name"
                :value="item.id"
              >
              </el-option>
            </el-select>
          </el-col>
          <el-col :span="4">
            民族:
            <el-select
              v-model="searchValue.nationId"
              size="mini"
              style="width: 130px"
              placeholder="民族"
            >
              <el-option
                v-for="item in nations"
                :key="item.id"
                :label="item.name"
                :value="item.id"
              >
              </el-option>
            </el-select>
          </el-col>
          <el-col :span="4">
            职位:
            <el-select
              v-model="searchValue.posId"
              size="mini"
              style="width: 130px"
              placeholder="职位"
            >
              <el-option
                v-for="item in positions"
                :key="item.id"
                :label="item.name"
                :value="item.id"
              >
              </el-option>
            </el-select>
          </el-col>
          <el-col :span="4">
            职称:
            <el-select
              v-model="searchValue.jobLevelId"
              size="mini"
              style="width: 130px"
              placeholder="职位"
            >
              <el-option
                v-for="item in joblevels"
                :key="item.id"
                :label="item.name"
                :value="item.id"
              >
              </el-option>
            </el-select>
          </el-col>
          <el-col :span="7">
            聘用形式:
            <el-radio-group v-model="searchValue.engageForm">
              <el-radio label="劳动合同">劳动合同</el-radio>
              <el-radio label="劳务合同">劳务合同</el-radio>
            </el-radio-group>
          </el-col>
        </el-row>

        <el-row style="margin-top: 10px">
          <el-col :span="5"> 
            所属部门:
            <el-popover
              placement="right"
              title="请选择部门"
              width="200"
              trigger="manual"
              v-model="visible2"
            >
              <el-tree
                default-expand-all
                :data="allDeps"
                :props="defaultProps"
                @node-click="searchHandleNodeClick"
              ></el-tree>
              <div slot="reference" class="depFrame" @click="visible2 = !visible2">
                {{ this.inputDepName }}
              </div>
            </el-popover>
          </el-col>
          <el-col :span="10">
            入职日期:
            <el-date-picker
              v-model="searchValue.beginDateScope"
              size="mini"
              type="daterange"
              value-format="yyyy-MM-dd"
              unlink-panels
              range-separator="至"
              start-placeholder="开始日期"
              end-placeholder="结束日期"
            >
            </el-date-picker>
          </el-col>
          <el-col :span="5" :offset="4">
            <el-button size="mini">取消</el-button>
            <el-button
              @click="initEmps('advanced')"
              size="mini"
              icon="el-icon-search"
              type="primary"
              >搜索
            </el-button>
          </el-col>
        </el-row>
      </div>
    </el-collapse-transition>
    <!-- 展示数据表格 -->
    <div>
      <el-table
        :data="emps"
        stripe
        v-loading="loading"
        element-loading-text="loading"
        element-loading-spinner="el-icon-loading"
        element-loading-background="rgba(0, 0, 0, 0.8)"
        border
        style="width: 100%; margin: 6px 0px 0px 0px"
      >
        <el-table-column type="selection" width="55"> </el-table-column>
        <el-table-column label="姓名" fixed width="90">
          <template slot-scope="scope">
            <el-tag>{{ scope.row.name }}</el-tag>
          </template>
        </el-table-column>
        <el-table-column prop="workID" label="工号" align="left" width="85">
        </el-table-column>
        <el-table-column prop="gender" label="性别" width="50">
        </el-table-column>
        <el-table-column
          prop="birthday"
          label="生日日期"
          align="left"
          width="95"
        >
        </el-table-column>
        <el-table-column
          prop="idCard"
          label="省份证号"
          align="left"
          width="150"
        >
        </el-table-column>
        <el-table-column prop="wedlock" label="婚姻状况" width="60">
        </el-table-column>
        <el-table-column prop="nation.name" label="民族" width="50">
        </el-table-column>
        <el-table-column prop="nativePlace" label="籍贯" width="80">
        </el-table-column>
        <el-table-column prop="politicsStatus.name" label="政治面貌" width="95">
        </el-table-column>
        <el-table-column prop="email" label="电子邮件" align="left" width="180">
        </el-table-column>
        <el-table-column prop="nativePlace" label="籍贯" width="80">
        </el-table-column>
        <el-table-column prop="phone" label="电话号码" align="left" width="100">
        </el-table-column>
        <el-table-column
          prop="address"
          label="联系地址"
          align="left"
          width="270"
        >
        </el-table-column>
        <el-table-column
          prop="department.name"
          label="所属部门"
          align="left"
          width="100"
        >
        </el-table-column>
        <el-table-column prop="joblevel.name" label="职称" width="100">
        </el-table-column>
        <el-table-column prop="position.name" label="职位" width="100">
        </el-table-column>
        <el-table-column prop="engageForm" label="聘用形式" width="80">
        </el-table-column>
        <el-table-column prop="tiptopDegree" label="最高学历" width="80">
        </el-table-column>
        <el-table-column prop="school" label="学校" align="left" width="150">
        </el-table-column>
        <el-table-column
          prop="workState"
          label="在职状态"
          align="left"
          width="70"
        >
        </el-table-column>
        <el-table-column
          prop="beginDate"
          label="入职日期"
          align="left"
          width="95"
        >
        </el-table-column>
        <el-table-column
          prop="conversionTime"
          label="转正日期"
          align="left"
          width="95"
        >
        </el-table-column>
        <el-table-column
          prop="beginContract"
          label="合同起始日期"
          align="left"
          width="95"
        >
        </el-table-column>
        <el-table-column
          prop="endContract"
          label="合同截至日期"
          align="left"
          width="95"
        >
        </el-table-column>
        <el-table-column label="合同期限" align="left" width="65">
          <template slot-scope="scope"
            >{{ scope.row.contractTerm }} 年</template
          >
        </el-table-column>
        <el-table-column label="操作" align="center" fixed="right" width="200">
          <template slot-scope="scope">
            <el-button
              @click="showEditView(scope.row)"
              style="padding: 5px"
              size="mini"
              >编辑</el-button
            >
            <el-button style="padding: 5px" size="mini" type="primary"
              >查看高级资料</el-button
            >
            <el-button
              style="padding: 5px"
              size="mini"
              type="danger"
              @click="deleteEmp(scope.row)"
              >删除</el-button
            >
          </template>
        </el-table-column>
      </el-table>
      <!-- 分页 -->
      <div style="display: flex; justify-content: flex-end">
        <el-pagination
          background
          @current-change="currentChange"
          @size-change="sizeChange"
          layout="prev, pager, next, sizes, jumper, ->, total"
          :total="total"
        >
        </el-pagination>
      </div>
      <!-- 新增页面弹出框 -->
      <el-dialog
        :title="title"
        :visible.sync="dialogVisible"
        width="80%"
        :before-close="handleClose"
      >
        <!-- 增加or编辑表单 -->
        <div>
          <el-form ref="empForm" :model="emp" :rules="rules">
            <!-- 第一行 -->
            <el-row>
              <el-col :span="6">
                <el-form-item label="姓名:" prop="name">
                  <el-input
                    size="mini"
                    clearable
                    style="width: 150px"
                    v-model="emp.name"
                    placeholder="请输入员工姓名"
                    prefix-icon="el-icon-edit"
                  ></el-input>
                </el-form-item>
              </el-col>
              <el-col :span="5">
                <el-form-item label="性别:" prop="gender">
                  <el-radio-group v-model="emp.gender">
                    <el-radio label="男">男</el-radio>
                    <el-radio label="女">女</el-radio>
                  </el-radio-group>
                </el-form-item>
              </el-col>
              <el-col :span="6">
                <el-form-item label="出生日期:" prop="birthday">
                  <el-date-picker
                    v-model="emp.birthday"
                    type="date"
                    size="mini"
                    value-format="yyyy-MM-dd"
                    style="width: 150px"
                    placeholder="出生日期"
                  >
                  </el-date-picker>
                </el-form-item>
              </el-col>
              <el-col :span="7">
                <el-form-item label="政治面貌:" prop="politicId">
                  <el-select
                    v-model="emp.politicId"
                    size="mini"
                    placeholder="政治面貌"
                    style="width: 150px"
                  >
                    <el-option
                      v-for="item in this.politicsStatus"
                      :key="item.id"
                      :label="item.name"
                      :value="item.id"
                    >
                    </el-option>
                  </el-select>
                </el-form-item>
              </el-col>
            </el-row>
            <!-- 第二行 -->
            <el-row>
              <el-col :span="6">
                <el-form-item
                  label="民族:"
                  prop="nationId"
                  style="width: 200px"
                >
                  <el-select
                    v-model="emp.nationId"
                    size="mini"
                    placeholder="民族"
                    style="width: 150px"
                  >
                    <el-option
                      v-for="item in this.nations"
                      :key="item.id"
                      :label="item.name"
                      :value="item.id"
                    >
                    </el-option>
                  </el-select>
                </el-form-item>
              </el-col>
              <el-col :span="5">
                <el-form-item label="籍贯:" prop="nativePlace">
                  <el-input
                    size="mini"
                    clearable
                    style="width: 120px"
                    v-model="emp.nativePlace"
                    placeholder="请输入籍贯"
                    prefix-icon="el-icon-edit"
                  ></el-input>
                </el-form-item>
              </el-col>
              <el-col :span="6">
                <el-form-item label="电子邮箱:" prop="email">
                  <el-input
                    v-model="emp.email"
                    size="mini"
                    style="width: 150px"
                    clearable
                    placeholder="请输入电子邮箱"
                    prefix-icon="el-icon-message"
                  ></el-input>
                </el-form-item>
              </el-col>
              <el-col :span="7">
                <el-form-item label="联系地址:" prop="address">
                  <el-input
                    v-model="emp.address"
                    size="mini"
                    style="width: 200px"
                    clearable
                    placeholder="请输入联系地址"
                    prefix-icon="el-icon-location"
                  ></el-input>
                </el-form-item>
              </el-col>
            </el-row>
            <!-- 第三行 -->
            <el-row>
              <el-col :span="6">
                <el-form-item label="职位:" prop="posId">
                  <el-select
                    v-model="emp.posId"
                    size="mini"
                    placeholder="职位"
                    style="width: 150px"
                  >
                    <el-option
                      v-for="item in this.positions"
                      :key="item.id"
                      :label="item.name"
                      :value="item.id"
                    >
                    </el-option>
                  </el-select>
                </el-form-item>
              </el-col>

              <el-col :span="5">
                <el-form-item label="职称:" prop="jobLevelId">
                  <el-select
                    v-model="emp.jobLevelId"
                    size="mini"
                    placeholder="职称"
                    style="width: 150px"
                  >
                    <el-option
                      v-for="item in this.joblevels"
                      :key="item.id"
                      :label="item.name"
                      :value="item.id"
                    >
                    </el-option>
                  </el-select>
                </el-form-item>
              </el-col>
              <el-col :span="6">
                <el-form-item label="所属部门:" prop="departmentId">
                  <el-popover
                    placement="right"
                    title="所属部门"
                    width="200"
                    trigger="manual"
                    v-model="visible"
                  >
                    <el-tree
                      default-expand-all
                      :data="allDeps"
                      :props="defaultProps"
                      @node-click="handleNodeClick"
                    ></el-tree>
                    <div slot="reference" class="depFrame" @click="showDepView">
                      {{ this.inputDepName }}
                    </div>
                  </el-popover>
                </el-form-item>
              </el-col>
              <el-col :span="7">
                <el-form-item label="电话号码:" prop="phone">
                  <el-input
                    v-model="emp.phone"
                    placeholder="请输入电话号码"
                    size="mini"
                    style="width: 200px"
                    prefix-icon="el-icon-phone"
                  ></el-input>
                </el-form-item>
              </el-col>
            </el-row>

            <!-- 第四行 -->
            <el-row>
              <el-col :span="6">
                <el-form-item label="工号:" prop="workID">
                  <el-input
                    disabled
                    v-model="emp.workID"
                    placeholder="emp.workID"
                    prefix-icon="el-icon-edit"
                    size="mini"
                    style="width: 150px"
                  />
                </el-form-item>
              </el-col>
              <el-col :span="5">
                <el-form-item label="学历:" prop="tiptopDegree">
                  <el-select
                    v-model="emp.tiptopDegree"
                    size="mini"
                    placeholder="学历"
                    style="width: 150px"
                  >
                    <el-option
                      v-for="item in tiptopDegrees"
                      :key="item"
                      :label="item"
                      :value="item"
                    >
                    </el-option>
                  </el-select>
                </el-form-item>
              </el-col>
              <el-col :span="6">
                <el-form-item label="毕业院校:" prop="school">
                  <el-input
                    class="col_3"
                    clearable
                    v-model="emp.school"
                    placeholder="请输入学校"
                    prefix-icon="el-icon-edit"
                    size="mini"
                    style="width: 150px"
                  ></el-input>
                </el-form-item>
              </el-col>
              <el-col :span="7">
                <el-form-item label="专业名称:" prop="specialty">
                  <el-input
                    class="col_4"
                    clearable
                    v-model="emp.specialty"
                    placeholder="请输入专业名称"
                    prefix-icon="el-icon-edit"
                    size="mini"
                    style="width: 200px"
                  ></el-input>
                </el-form-item>
              </el-col>
            </el-row>

            <el-row>
              <el-col :span="6">
                <el-form-item label="入职日期:" prop="beginDate">
                  <el-date-picker
                    v-model="emp.beginDate"
                    type="date"
                    size="mini"
                    value-format="yyyy-MM-dd"
                    style="width: 150px"
                    placeholder="入职日期"
                  >
                  </el-date-picker>
                </el-form-item>
              </el-col>
              <el-col :span="5">
                <el-form-item label="转正日期:" prop="conversionTime">
                  <el-date-picker
                    v-model="emp.conversionTime"
                    type="date"
                    size="mini"
                    value-format="yyyy-MM-dd"
                    style="width: 130px"
                    placeholder="转正日期"
                  >
                  </el-date-picker>
                </el-form-item>
              </el-col>
              <el-col :span="6">
                <el-form-item label="合同起始日期:" prop="benginContarct">
                  <el-date-picker
                    v-model="emp.beginContract"
                    type="date"
                    size="mini"
                    value-format="yyyy-MM-dd"
                    style="width: 130px"
                    placeholder="合同起始日期"
                  >
                  </el-date-picker>
                </el-form-item>
              </el-col>
              <el-col :span="7">
                <el-form-item label="合同截至日期:" prop="endContarct">
                  <el-date-picker
                    v-model="emp.endContract"
                    type="date"
                    size="mini"
                    value-format="yyyy-MM-dd"
                    style="width: 173px"
                    placeholder="合同截至日期"
                  >
                  </el-date-picker>
                </el-form-item>
              </el-col>
            </el-row>

            <el-row>
              <el-col :span="8">
                <el-form-item label="身份证:" prop="idCard">
                  <el-input
                    v-model="emp.idCard"
                    placeholder="请输入身份证号码"
                    clearable
                    size="mini"
                    style="width: 180px"
                  ></el-input>
                </el-form-item>
              </el-col>
              <el-col :span="8">
                <el-form-item label="聘用形式:" prop="engageForm">
                  <el-radio-group v-model="emp.engageForm">
                    <el-radio label="劳务合同">劳务合同</el-radio>
                    <el-radio label="劳动合同">劳动合同</el-radio>
                  </el-radio-group>
                </el-form-item>
              </el-col>
              <el-col :span="8">
                <el-form-item label="婚姻状况:" prop="wedlock">
                  <el-radio-group v-model="emp.wedlock">
                    <el-radio label="已婚">已婚</el-radio>
                    <el-radio label="未婚">未婚</el-radio>
                  </el-radio-group>
                </el-form-item>
              </el-col>
            </el-row>
          </el-form>
        </div>
        <span slot="footer" class="dialog-footer">
          <el-button @click="dialogVisible = false">取 消</el-button>
          <el-button type="primary" @click="doAddOrEditEmp">确 定</el-button>
        </span>
      </el-dialog>
    </div>
  </div>
</template>

<script>
export default {
  name: "EmpBasic",
  data() {
    return {
      title: "",
      visible: false,
      visible2: false,
      inputDepName: "",
      emps: [],
      allDeps: [],
      loading: false,
      total: 0,
      page: 1,
      size: 10,
      empName: "",
      dialogVisible: false,
      advancedSearchVisible: false,
      options: [],
      nations: [],
      joblevels: [],
      positions: [],
      politicsStatus: [],
      tiptopDegrees: [
        "博士",
        "硕士",
        "本科",
        "大专",
        "高中",
        "初中",
        "小学",
        "其他",
      ],
      defaultProps: {
        children: "children",
        label: "name",
      },
      emp: {
        id: null,
        name: "",
        gender: "",
        birthday: "",
        idCard: "",
        wedlock: "",
        nationId: null,
        nativePlace: "",
        politicId: null,
        email: "",
        phone: "",
        address: "",
        departmentId: null,
        jobLevelId: null,
        posId: null,
        engageForm: "",
        tiptopDegree: "",
        specialty: "",
        school: "",
        beginDate: "",
        workState: "在职",
        workID: "",
        contractTerm: null,
        conversionTime: "",
        notWorkDate: null,
        beginContract: "",
        endContract: "",
        workAge: null,
        salaryId: null,
      },
      rules: {
        name: [{ required: true, message: "请输入员工姓名", trigger: "blur" }],
        // gender: [{required: true, message: '请输入员工性别', trigger: 'blur'}],
        // birthday: [{required: true, message: '请输入生出日期', trigger: 'blur'}],
        idCard: [
          { required: true, message: "请输入身份证号码", trigger: "blur" },
          {
            pattern:
              /(^[1-9]\d{5}(18|19|([23]\d))\d{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)\d{3}[0-9Xx]$)|(^[1-9]\d{5}\d{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)\d{2}$)/,
            message: "身份证号码不正确",
            trigger: "blur",
          },
        ],
        // wedlock: [{required: true, message: '请输入婚姻状况', trigger: 'blur'}],
        // nationId: [{required: true, message: '请输入民族', trigger: 'blur'}],
        // nativePlace: [{required: true, message: '请输入籍贯', trigger: 'blur'}],
        // politicId: [{required: true, message: '请输入政治面貌', trigger: 'blur'}],
        email: [
          { required: true, message: "请输入邮箱地址", trigger: "blur" },
          {
            type: "email",
            message: "邮箱地址格式不正确",
            trigger: "blur",
          },
        ],
        phone: [{ required: true, message: "请输入电话号码", trigger: "blur" }],
        // address: [{required: true, message: '请输入员工地址', trigger: 'blur'}],
        // departmentId: [{required: true, message: '请输入部门名称', trigger: 'blur'}],
        // jobLevelId: [{required: true, message: '请输入职称', trigger: 'blur'}],
        // posId: [{required: true, message: '请输入职位', trigger: 'blur'}],
        engageForm: [
          { required: true, message: "请输入聘用形式", trigger: "blur" },
        ],
        // tiptopDegree: [{required: true, message: '请输入学历', trigger: 'blur'}],
        // specialty: [{required: true, message: '请输入专业', trigger: 'blur'}],
        // school: [{required: true, message: '请输入毕业院校', trigger: 'blur'}],
        beginDate: [
          { required: true, message: "请输入入职日期", trigger: "blur" },
        ],
        // workState: [{required: true, message: '请输入工作状态', trigger: 'blur'}],
        // workID: [{required: true, message: '请输入工号', trigger: 'blur'}],
        // contractTerm: [{required: true, message: '请输入合同期限', trigger: 'blur'}],
        // conversionTime: [{required: true, message: '请输入转正日期', trigger: 'blur'}],
        // notWorkDate: [{required: true, message: '请输入离职日期', trigger: 'blur'}],
        // beginContract: [{required: true, message: '请输入合同起始日期', trigger: 'blur'}],
        // endContract: [{required: true, message: '请输入合同结束日期', trigger: 'blur'}],
        // workAge: [{required: true, message: '请输入工龄', trigger: 'blur'}],
      },
      searchValue: {
        politicId: '',
        nationId: '',
        posId: '',
        jobLevelId: '',
        engageForm: '',
        departmentId: '',
        beginDateScope: '',
      },
    };
  },
  methods: {
    exportData() {
      this.getRequest("/employee/basic/export").then((resp) => {
        this.downloadRequest("/employee/basic/export");
      });
    },
    showEditView(data) {
      this.title = "编辑员工信息";
      this.emp = data;
      this.initPosition();
      this.inputDepName = data.department.name;
      this.dialogVisible = true;
    },
    deleteEmp(data) {
      this.$confirm(
        "此操作将永久删除[" + data.name + "]员工, 是否继续?",
        "提示",
        {
          confirmButtonText: "确定",
          cancelButtonText: "取消",
          type: "warning",
        }
      )
        .then(() => {
          this.deleteRequest("/employee/basic/" + data.id).then((resp) => {
            if (resp) {
              this.initEmps();
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
    doAddOrEditEmp() {
      if (this.emp.id) {
        this.$refs["empForm"].validate((valid) => {
          if (valid) {
            this.putRequest("/employee/basic/", this.emp).then((resp) => {
              if (resp) {
                this.dialogVisible = false;
                this.initEmps();
              }
            });
          }
        });
      } else {
        this.$refs["empForm"].validate((valid) => {
          if (valid) {
            this.postRequest("/employee/basic/", this.emp).then((resp) => {
              if (resp) {
                this.dialogVisible = false;
                this.initEmps();
              }
            });
          }
        });
      }
    },
    handleNodeClick(data) {
      this.inputDepName = data.name;
      this.emp.departmentId = data.id;
      this.visible = !this.visible;
    },
    searchHandleNodeClick(data){
      this.visible2 = !this.visible2;
      this.inputDepName = data.name;
      this.searchValue.departmentId = data.id;
    },
    showDepView() {
      this.visible = !this.visible;
    },
    getMaxWorkID() {
      this.getRequest("/employee/basic/maxWorkID").then((resp) => {
        this.emp.workID = resp.obj;
      });
    },

    initPosition() {
      this.getRequest("/employee/basic/positions").then((resp) => {
        this.positions = resp;
      });
    },
    initData() {
      // 很少修改的数据存放在sessionStorage中
      if (!window.sessionStorage.getItem("nations")) {
        this.getRequest("/employee/basic/nations").then((resp) => {
          this.nations = resp;
          window.sessionStorage.setItem("nations", JSON.stringify(resp));
        });
      } else {
        this.nations = JSON.parse(window.sessionStorage.getItem("nations"));
      }
      if (!window.sessionStorage.getItem("joblevels")) {
        this.getRequest("/employee/basic/joblevels").then((resp) => {
          this.joblevels = resp;
          window.sessionStorage.setItem("joblevels", JSON.stringify(resp));
        });
      } else {
        this.joblevels = JSON.parse(window.sessionStorage.getItem("joblevels"));
      }
      if (!window.sessionStorage.getItem("politicsStatus")) {
        this.getRequest("/employee/basic/politicsStatus").then((resp) => {
          this.politicsStatus = resp;
          window.sessionStorage.setItem("politicsStatus", JSON.stringify(resp));
        });
      } else {
        this.politicsStatus = JSON.parse(
          window.sessionStorage.getItem("politicsStatus")
        );
      }
      if (!window.sessionStorage.getItem("allDeps")) {
        this.getRequest("/employee/basic/departments").then((resp) => {
          this.allDeps = resp;
          window.sessionStorage.setItem("allDeps", JSON.stringify(resp));
        });
      } else {
        this.allDeps = JSON.parse(window.sessionStorage.getItem("allDeps"));
      }
    },
    handleClose() {
      this.dialogVisible = false;
    },
    showAddView() {
      this.title = "添加员工";
      this.inputDepName = "";
      this.getMaxWorkID();
      this.initPosition();
      this.dialogVisible = true;
      this.emp = {
        id: null,
        name: "",
        gender: "",
        birthday: "",
        idCard: "",
        wedlock: "",
        nationId: null,
        nativePlace: "",
        politicId: null,
        email: "",
        phone: "",
        address: "",
        departmentId: null,
        jobLevelId: null,
        posId: null,
        engageForm: "",
        tiptopDegree: "",
        specialty: "",
        school: "",
        beginDate: "",
        workState: "在职",
        workID: "",
        contractTerm: null,
        conversionTime: "",
        notWorkDate: null,
        beginContract: "",
        endContract: "",
        workAge: null,
        salaryId: null,
      };
    },
    currentChange(currentPage) {
      this.page = currentPage;
      this.initEmps();
    },
    sizeChange(size) {
      this.size = size;
      this.initEmps();
    },
    initEmps(type) {
      this.loading = true;
      let url = '/employee/basic/?currentPage=' + this.page;
      url += '&size=' + this.size;
      url += '&name=' + this.empName;
      // url += '&politicId=' + this.searchValue.politicId;
      // url += '&nationId=' + this.searchValue.nationId;
      // url += '&posId=' + this.searchValue.posId;
      // url += '&jobLevelId=' + this.searchValue.jobLevelId;
      // url += '&engageForm=' + this.searchValue.engageForm;
      // url += '&departmentId=' + this.searchValue.departmentId;
      // url += '&beginDateScope=' + this.searchValue.beginDateScope;

      let keys = Object.keys(this.searchValue);
      // console.log(keys)
      keys.forEach(key => {
        url += '&'+key+'=' + this.searchValue[key];
      });
      // console.log(url);

      this.getRequest(
        url
      ).then((resp) => {
        this.loading = false;
        if (resp) {
          this.emps = resp.data;
          this.total = resp.total;
        }
      });
    },
    initPoliticsStatus() {
      this.getRequest("/employee/basic/politicsStatus").then((resp) => {
        if (resp) {
          this.politicsStatus = resp;
        }
      });
    },
  },
  mounted() {
    this.initEmps();
    this.initData();
    this.initPosition();
    this.initPoliticsStatus();
  },
};
</script>

<style scoped>
.col_1 {
  width: 150px;
}
.el-dialog .el-radio-group {
  margin-top: 9px;
}
.depFrame {
  box-sizing: border-box;
  width: 150px;
  display: inline-flex;
  margin-top: 4px;
  border: 1px solid #dedede;
  height: 26.3px;
  border-radius: 5px;
  cursor: pointer;

  line-height: 26.3px;
  font-size: 13px;
  align-items: center;
  padding-left: 8px;
}

/* .transition-box {
  margin-bottom: 10px;
  width: 200px;
  height: 100px;
  border-radius: 4px;
  background-color: #409eff;
  text-align: center;
  color: #fff;
  padding: 40px 20px;
  box-sizing: border-box;
  margin-right: 20px;
} */
</style>
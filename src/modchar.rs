pub trait ModChar {
    fn is_u8_under_dollar(&self) -> bool; // underscore or dollar
    fn is_u8_alnum_or_under_dollar(&self) -> bool;
    fn is_u8_double_single(&self) -> bool; // double, single or back quotues/ticks
}

impl ModChar for u8 {
  fn is_u8_under_dollar(&self) -> bool {
      *self == 95 || *self == 36
  }

  fn is_u8_alnum_or_under_dollar(&self) -> bool {
      self.is_ascii_alphanumeric() || self.is_u8_under_dollar()
  }

  fn is_u8_double_single(&self) -> bool {
      *self == 34 || *self == 39 || *self == 96
  }

}

module cnz_test
  implicit none
  interface fib
     module procedure fib
  end interface fib

  contains

  recursive function fib (n)  result (fnum)
    integer(kind=8), intent(in)  :: n
    integer(kind=8) :: fnum
    if (n==0) then
       fnum = 0
    else if (n==1) then
       fnum = 1
    else 
       fnum = fib(n-1) + fib(n-2)
    endif
  end function fib

end module cnz_test

module cnz_str_to_int
  contains
  elemental subroutine str_to_int(str_value,int_val,stat)
    implicit none
    ! The args
    character(len=*),intent(in) :: str_value
    integer(kind=8),intent(out) :: int_val
    integer(kind=8),intent(out) :: stat
    read(str_value,*,iostat=stat)  int_val
  end subroutine str_to_int
end module

program MAIN
  use cnz_test, only: fib
  use cnz_str_to_int
  use, intrinsic:: iso_fortran_env, only: stdout=>output_unit

  implicit none

  integer(kind=8) :: num
  integer(kind=8) :: int_value, stat
  real :: start, finish
  integer :: num_args, ix
  character(len=12), dimension(:), allocatable :: args
  num_args = command_argument_count()
  allocate(args(num_args))
  num = 10
  do ix = 1, num_args
    call get_command_argument(ix,args(ix))
    call str_to_int(args(ix), int_value, stat)
    if (stat == 0 ) then
      num = int_value
    else
      print *,'Fail to convert number!!'
    endif
  end do
  PRINT '(4g0)', "************************* ", "FORTRAN 90", " *************************"
  call cpu_time(start)
  PRINT '(4g0)', "fib(", num, ")=", fib(num)
  call cpu_time(finish)
  print '("Time = ",f6.3," seconds.")',finish-start
end program


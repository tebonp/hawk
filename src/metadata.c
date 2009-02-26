#include "configuration.h"
#include <ctype.h>

Options global_options;

static int depends_on_diff_map(const Options * opt){
  if(opt->algorithm == DIFF_MAP){
    return 1;
  }
  return 0;
}


static int depends_on_initial_guess_from_autocorrelation(const Options * opt){
  if(opt->image_guess_filename[0] == 0){
    return 1;
  }
  return 0;
}

static int depends_on_amplitudes_file(const Options * opt){
  if(opt->diffraction_filename[0] != 0){
    return 1;
  }
  return 0;
}

static int depends_on_no_amplitudes_file(const Options * opt){
  if(opt->diffraction_filename[0] == 0){
    return 1;
  }
  return 0;
}

static int depends_on_no_realspace_image_file(const Options * opt){
  if(opt->image_guess_filename[0] == 0){
    return 1;
  }
  return 0;
}

static int depends_on_patterson_algorithm_fixed(const Options * opt){  
  if(depends_on_initial_guess_from_autocorrelation(opt)
     && opt->patterson_level_algorithm == FIXED){
    return 1;
  }
  return 0;
}

static int depends_on_patterson_algorithm_constant_area(const Options * opt){  
  if(depends_on_initial_guess_from_autocorrelation(opt)
     && opt->patterson_level_algorithm == CONSTANT_AREA){
    return 1;
  }
  return 0;
}

static int depends_on_phasing_algorithm_is_cflip(const Options * opt){  
  if(opt->algorithm == CFLIP){
    return 1;
  }
  return 0;
}

static int depends_on_phasing_algorithm_is_raar(const Options * opt){  
  if(opt->algorithm == RAAR){
    return 1;
  }
  return 0;
}

static int depends_on_phasing_algorithm_with_positivity(const Options * opt){  
  if(opt->algorithm == RAAR || opt->algorithm == HIO ||
     opt->algorithm == HPR || opt->algorithm == CFLIP){
    return 1;
  }
  return 0;
}

static int depends_on_phasing_algorithm_with_enforce_real(const Options * opt){  
  if(opt->algorithm == RAAR || opt->algorithm == HIO ||
     opt->algorithm == HPR || opt->algorithm == CFLIP){
    return 1;
  }
  return 0;
}

static int depends_on_phasing_algorithm_with_beta(const Options * opt){  
  if(opt->algorithm == RAAR || opt->algorithm == HIO ||
     opt->algorithm == HPR || opt->algorithm == RAAR_PROJ ||
     opt->algorithm == HIO_PROJ || opt->algorithm == DIFF_MAP){
    return 1;
  }
  return 0;
}

static int depends_on_phasing_algorithm_with_perturb_reflections(const Options * opt){  
  if(opt->algorithm == RAAR || opt->algorithm == CFLIP){
    return 1;
  }
  return 0;
}

static int depends_on_support_algorithm_with_threshold(const Options * opt){  
  if(opt->support_update_algorithm == FIXED ||
     opt->support_update_algorithm == STEPPED){
    return 1;
  }
  return 0;
}

static int depends_on_support_algorithm_with_area(const Options * opt){  
  if(opt->support_update_algorithm == CONSTANT_AREA ||
     opt->support_update_algorithm == DECREASING_AREA||
     opt->support_update_algorithm == COMPLEX_DECREASING_AREA){
    return 1;
  }
  return 0;
}

static int depends_on_support_algorithm_with_changing_area(const Options * opt){  
  if(opt->support_update_algorithm == DECREASING_AREA ||
     opt->support_update_algorithm == COMPLEX_DECREASING_AREA){
    return 1;
  }
  return 0;
}

static int depends_on_support_algorithm_with_real_error_threshold(const Options * opt){  
  if(opt->support_update_algorithm == REAL_ERROR_ADAPTATIVE ||
     opt->support_update_algorithm == REAL_ERROR_CAPPED){
    return 1;
  }
  return 0;
}


VariableMetadata variable_metadata[200] = {
  {
    .variable_name = "ROOT",
    .variable_type = Type_Group,
    .id = Id_Root,
    .parent = NULL,
    .variable_properties = isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.diffraction_filename),
    .documentation = "The base group",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "input_data",
    .display_name = "Input Data",
    .variable_type = Type_Group,
    .id = Id_Input,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = NULL,
    .documentation = "The group that contains the options relevant to the input data to be phased.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "amplitudes_file",
    .display_name = "Amplitudes File",
    .variable_type = Type_Filename,
    .id = Id_Diffraction_Filename,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.diffraction_filename),
    .documentation = "The input h5 file that contains the experimental diffraction amplitudes (not the intensities), with the center determined and with the quadrants shifted.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "max_blur_radius",
    .display_name = "Max Blur Radius",
    .variable_type = Type_Real,
    .id = Id_Max_Blur_Radius,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.max_blur_radius),
    .documentation = "Correponds to 3 times the maximum standard deviation of the gaussian blur applied before doing any further processing to the real space image guess."
    " The real space image guess is then passed on to the rest of the computing chain that calculates the new support."
    " This option only affects the support calculation routines."
    " Typically there is a maximum and a minimum blur radius which the program smoothly interpolates in between during the first iterations_to_min_blur iterations",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "patterson_threshold",
    .variable_type = Type_Real,
    .id = Id_Init_Level,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.init_level),
    .documentation = "Corresponds to a fraction of the maximum value of a pixel in the autocorrelation image."
    " After normalizing to the maximum value pixels which have a value higher than this fraction will be included in the support.",
    .dependencies = depends_on_patterson_algorithm_fixed,
    .reserved = NULL
  },
  {
    .variable_name = "beta",
    .display_name = "Beta",
    .variable_type = Type_Real,
    .id = Id_Beta,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.beta),
    .documentation = "Relaxation parameter used in several algorithms. Please refer to the specific algorithm documentation for more information.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "innerloop_iterations",
    .display_name = "Innerloop Iterations",
    .variable_type = Type_Int,
    .id = Id_Iterations,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.iterations),
    .documentation = "Number of iterations of the phasing basic algorithm which are performed in between the support update steps.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "fixed_support_mask",
    .display_name = "Fixed Support Mask",
    .variable_type = Type_Filename,
    .id = Id_Support_Mask_Filename,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.support_mask_filename),
    .documentation = "The name of an .h5 file which defines a mask that will be added to the support after every support update."
    " The pixels of the image file with a value different than 0 will be added to the support. "
    " The new support will then be the union of the original support with the pixels of the fixed_support_mask file which are different than 0."
    " Please note that the mask field of the fixed_support_mask file is totally irrelevant.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "initial_support",
    .display_name = "Initial Support",
    .variable_type = Type_Filename,
    .id = Id_Init_Support_Filename,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.init_support_filename),
    .documentation = "The file name of the support that is used to start the reconstruction. If no file is given the"
    " initial support is derived from the autocorrelation.",
    .dependencies = NULL,
    .reserved = NULL  
  },
  {
    .variable_name = "image_guess",
    .variable_type = Type_Filename,
    .id = Id_Image_Guess_Filename,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.image_guess_filename),
    .documentation = "The file name of the real space starting image for the reconstruction. If no file is given the"
    " initial image is derived from the autocorrelation.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "added_noise",
    .variable_type = Type_Real,
    .id = Id_Noise,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.noise),
    .documentation = "Obsolete option",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "beamstop_radius",
    .variable_type = Type_Real,
    .id = Id_Beamstop,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.beamstop),
    .documentation = "Obsolete option",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "support_intensity_threshold",
    .variable_type = Type_Real,
    .id = Id_New_Level,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.new_level),
    .documentation = "This setting only has any effect when used in conjunction with fixed support update. It's value is a fraction of the intensity of the most intense pixels."
    " During the calculation of the new support only pixels for which the normalized intensity (normalized to the most intense pixel) is greater than the support_intensity_threshold "
    " are kept in the support. For example for a support_intensity_threshold = 0.4 and for an image with the highest pixel intensity of 34000, all pixels above 13600 would be retained in the support.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "iterations_to_min_blur",
    .variable_type = Type_Int,
    .id = Id_Iterations_To_Min_Blur,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.iterations_to_min_blur),
    .documentation = "During the support update procedure the real space image is blured with a gaussian. This gaussian starts with a radius of max_blur_radius and gradually decreases to"
    "minimum_blur_radius after iterations_to_min_blur iterations.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "blur_radius_reduction_method",
    .variable_type = Type_MultipleChoice,
    .id = Id_Blur_Radius_Reduction_Method,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {GAUSSIAN_BLUR_REDUCTION,GEOMETRICAL_BLUR_REDUCTION,0},
    .list_valid_names = {"gaussian","geometrical",0},
    .variable_address = &(global_options.blur_radius_reduction_method),
    .documentation = "Specifies the function used for interpolation between the max and the minimum of the blur radius.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "minimum_blur_radius",
    .variable_type = Type_Real,
    .id = Id_Min_Blur,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.min_blur),
    .documentation = "During the support update procedure the real space image is blured with a gaussian. This gaussian starts with a radius of max_blur_radius and gradually decreases to"
    "minimum_blur_radius after iterations_to_min_blur iterations.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "logging",
    .display_name = "Logging",
    .variable_type = Type_Group,
    .id = Id_Logging,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = NULL,
    .documentation = "The group that contains the options relevant to log files.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "commandline",
    .variable_type = Type_String,
    .id = Id_Commandline,
    .parent = &(variable_metadata[0]),
    .variable_properties = isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.commandline),
    .documentation = "Command line that was used to invoke the program.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "output_period",
    .display_name = "Images Output Period",
    .variable_type = Type_Int,
    .id = Id_Output_Period,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.output_period),
    .documentation = "The number of iterations between writing images to files. For example a value of 100 means that the program will output images at step 0,99,199,etc...",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "log_output_period",
    .display_name = "Log Output Period",
    .variable_type = Type_Int,
    .id = Id_Log_Output_Period,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.log_output_period),
    .documentation = "The number of iterations between writing statistics to the log file. For example a value of 20 means that the program will output images at step 0,19,39,etc...",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "phasing_method",
    .display_name = "Phasing Method",
    .variable_type = Type_Group,
    .id = Id_Phasing,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = NULL,
    .documentation = "This group contains all the options related to the phasing algorithms",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "RAAR_sigma",
    .variable_type = Type_Real,
    .id = Id_Exp_Sigma,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.exp_sigma),
    .documentation = "When using the RAAR algorithm the image amplitudes are allowed to deviate from input amplitudes by a fraction of their value. This fraction is given by the RAAR_sigma."
    " For example if RAAR_sigma is 0.05 then a pixel with an amplitude of 100 would be allowed to range between 95 and 105. The way the value is constrained is by using the so called modulus annulus projection."
    "For more information about the modulus annulus projection please see Pierre Thibault PhD thesis section 3.4.1.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "dynamic_beta",
    .variable_type = Type_Real,
    .id = Id_Dyn_Beta,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.dyn_beta),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "random_initial_phases",
    .variable_type = Type_Bool,
    .id = Id_Rand_Phases,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.rand_phases),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "random_initial_intensities",
    .variable_type = Type_Bool,
    .id = Id_Rand_Intensities,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.rand_intensities),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "cur_iteration",
    .variable_type = Type_Int,
    .id = Id_Cur_Iteration,
    .parent = &(variable_metadata[0]),
    .variable_properties = isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.cur_iteration),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "adapt_thres",
    .variable_type = Type_Bool,
    .id = Id_Adapt_Thres,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.adapt_thres),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "automatic",
    .variable_type = Type_Bool,
    .id = Id_Automatic,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.dyn_beta),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "work_directory",
    .display_name = "Working Directory",
    .variable_type = Type_Directory_Name,
    .id = Id_Work_Dir,
    .parent = &(variable_metadata[16]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.work_dir),
    .documentation = "The directory well the output is going to be written to.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "support_real_error_threshold",
    .variable_type = Type_Real,
    .id = Id_Real_Error_Threshold,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.real_error_threshold),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "support_update_method",
    .display_name = "Support Update Method",
    .variable_type = Type_Group,
    .id = Id_Support,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = NULL,
    .documentation = "Contains the options relevant to the way the support is updated",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "output_precision",
    .display_name = "Output Precision",
    .variable_type = Type_Int,
    .id = Id_Output_Precision,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.output_precision),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "error_reduction_iterations_after_loop",
    .variable_type = Type_Int,
    .id = Id_Error_Reduction_Iterations_After_Loop,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.error_reduction_iterations_after_loop),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "enforce_positivity",
    .variable_type = Type_Real,
    .id = Id_Enforce_Positivity,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.enforce_positivity),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "enforce_real",
    .variable_type = Type_Int,
    .id = Id_Enforce_Real,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.enforce_real),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "genetic_optimization",
    .variable_type = Type_Bool,
    .id = Id_Genetic_Optimization,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.genetic_optimization),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "charge_flip_sigma",
    .variable_type = Type_Real,
    .id = Id_Charge_Flip_Sigma,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.charge_flip_sigma),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "rescale_amplitudes",
    .variable_type = Type_Bool,
    .id = Id_Rescale_Amplitudes,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.rescale_amplitudes),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "square_mask",
    .variable_type = Type_Real,
    .id = Id_Square_Mask,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.square_mask),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "patterson_blur_radius",
    .variable_type = Type_Real,
    .id = Id_Patterson_Blur_Radius,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.patterson_blur_radius),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "remove_central_pixel_phase",
    .variable_type = Type_Bool,
    .id = Id_Remove_Central_Pixel_phase,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.remove_central_pixel_phase),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "perturb_weak_reflections",
    .variable_type = Type_Real,
    .id = Id_Perturb_Weak_Reflections,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.perturb_weak_reflections),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "nthreads",
    .display_name = "Number of Threads",
    .variable_type = Type_Int,
    .id = Id_Nthreads,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.nthreads),
    .documentation = "Number of threads used by the program during the FFTs",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "break_centrosym_period",
    .variable_type = Type_Int,
    .id = Id_Break_Centrosym_Period,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.break_centrosym_period),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "reconstruction_finished",
    .variable_type = Type_Bool,
    .id = Id_Reconstruction_Finished,
    .parent = &(variable_metadata[0]),
    .variable_properties = isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.reconstruction_finished),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "real_error_tolerance",
    .variable_type = Type_Real,
    .id = Id_Real_Error_Tolerance,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.real_error_tolerance),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "max_iterations",
    .display_name = "Maximum Iterations",
    .variable_type = Type_Int,
    .id = Id_Max_Iterations,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|withSpecialValue,
    .list_valid_values = {0,0},
    .list_valid_names = {"Infinity",0},
    .variable_address = &(global_options.max_iterations),
    .documentation = "The reconstruction stops after this number of iterations.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "patterson_level_algorithm",
    .variable_type = Type_MultipleChoice,
    .id = Id_Patterson_Level_Algorithm,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {FIXED,STEPPED,REAL_ERROR_CAPPED,REAL_ERROR_ADAPTATIVE,CONSTANT_AREA,DECREASING_AREA,0},
    .list_valid_names = {"fixed","stepped","real_error_capped","real_error_adaptative","constant_area","decreasing_area",0},
    .variable_address = &(global_options.patterson_level_algorithm),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "object_area",
    .variable_type = Type_Real,
    .id = Id_Object_Area,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.object_area),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "image_blur_period",
    .variable_type = Type_Int,
    .id = Id_Image_Blur_Period,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.image_blur_period),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "image_blur_radius",
    .variable_type = Type_Real,
    .id = Id_Image_Blur_Radius,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.image_blur_radius),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "iterations_to_min_object_area",
    .variable_type = Type_Int,
    .id = Id_Iterations_To_Min_Object_Area,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.iterations_to_min_object_area),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "min_object_area",
    .variable_type = Type_Real,
    .id = Id_Min_Object_Area,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.min_object_area),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "current_real_space_image",
    .variable_type = Type_Image,
    .id = Id_Current_Real_Space_Image,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableDuringRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.current_real_space_image),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "current_support",
    .variable_type = Type_Image,
    .id = Id_Current_Support,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableDuringRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.current_support),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "solution_file",
    .display_name = "Solution File",
    .variable_type = Type_Filename,
    .id = Id_Solution_File,
    .parent = &(variable_metadata[1]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isSettableDuringRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.solution_filename),
    .documentation = "File containing the exact solution. When provided, the correlation coefficient between the current image and the solution is outputed.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "phases_min_blur_radius",
    .variable_type = Type_Real,
    .id = Id_Phases_Min_Blur_Radius,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.phases_min_blur_radius),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "phases_max_blur_radius",
    .variable_type = Type_Real,
    .id = Id_Phases_Max_Blur_Radius,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.phases_max_blur_radius),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "iterations_to_min_phases_blur",
    .variable_type = Type_Int,
    .id = Id_Iterations_To_Min_Phases_Blur,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.iterations_to_min_phases_blur),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "intensities_std_dev_file",
    .variable_type = Type_Filename,
    .id = Id_Solution_File,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.intensities_std_dev_filename),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "autocorrelation_support_file",
    .variable_type = Type_Filename,
    .id = Id_Autocorrelation_Support_File,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.autocorrelation_support_filename),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "filter_intensities",
    .variable_type = Type_Bool,
    .id = Id_Filter_Intensities,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.filter_intensities),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "object_area_checkpoints",
    .variable_type = Type_Vector_Int,
    .id = Id_Object_Area_Checkpoints,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.object_area_checkpoints),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "object_area_at_checkpoints",
    .variable_type = Type_Vector_Real,
    .id = Id_Object_Area_at_Checkpoints,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.object_area_at_checkpoints),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "beta_checkpoints",
    .variable_type = Type_Vector_Int,
    .id = Id_Beta_Checkpoints,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.beta_checkpoints),
    .documentation = "Check points given as the iteration number for which beta should take a certain value.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "beta_at_checkpoints",
    .variable_type = Type_Vector_Real,
    .id = Id_Beta_at_Checkpoints,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.beta_at_checkpoints),
    .documentation = "The value of beta for each checkpoint. The checkpoints are set in beta_checkpoints.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "gamma1",
    .variable_type = Type_Real,
    .id = Id_Gamma1,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.gamma1),
    .documentation = "Gamma1 or Gamma_S parameter of the difference map algorithm.",
    .dependencies = depends_on_diff_map,
    .reserved = NULL
  },
  {
    .variable_name = "gamma2",
    .variable_type = Type_Real,
    .id = Id_Gamma2,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.gamma2),
    .documentation = "Gamma2 or Gamma_F parameter of the difference map algorithm.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "support_image_averaging",
    .variable_type = Type_Int,
    .id = Id_Support_Image_Averaging,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.support_image_averaging),
    .documentation = "The number of real_out images used the calculation of the support. Each image comes from a different iteration and their are averaged together",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "random_seed",
    .display_name = "Random Seed",
    .variable_type = Type_Int,
    .id = Id_Random_Seed,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|withSpecialValue|advanced,
    .list_valid_values = {-1,0},
    .list_valid_names = {"auto",0},
    .variable_address = &(global_options.random_seed),
    .documentation = "Seed used for the random number generators. If not set the process PID is used.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "added_noise",
    .display_name = "Added Noise",
    .variable_type = Type_Real,
    .id = Id_Noise,
    .parent = &(variable_metadata[1]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun|advanced|withSpecialValue,
    .list_valid_values = {0,0},
    .list_valid_names = {"off",0},
    .variable_address = &(global_options.noise),
    .documentation = "Obsolete option",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "beamstop_radius",
    .display_name = "Beamstop Radius",
    .variable_type = Type_Real,
    .id = Id_Beamstop,
    .parent = &(variable_metadata[1]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun|advanced|withSpecialValue,
    .list_valid_values = {0,0},
    .list_valid_names = {"off",0},
    .variable_address = &(global_options.beamstop),
    .documentation = "Obsolete option",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "maximum_blur_radius",
    .display_name = "Maximum Blur Radius",
    .variable_type = Type_Real,
    .id = Id_Max_Blur_Radius,
    .parent = &(variable_metadata[30]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun|advanced|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.max_blur_radius),
    .documentation = "Correponds to 3 times the maximum standard deviation of the gaussian blur applied before doing any further processing to the real space image guess."
    " The real space image guess is then passed on to the rest of the computing chain that calculates the new support."
    " This option only affects the support calculation routines."
    " Typically there is a maximum and a minimum blur radius which the program smoothly interpolates in between during the first iterations_to_min_blur iterations",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "fixed_support_mask",
    .display_name = "Fixed Support Mask",
    .variable_type = Type_Filename,
    .id = Id_Support_Mask_Filename,
    .parent = &(variable_metadata[30]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun|advanced,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.support_mask_filename),
    .documentation = "The name of an .h5 file which defines a mask that will be added to the support after every support update."
    " The pixels of the image file with a value different than 0 will be added to the support. "
    " The new support will then be the union of the original support with the pixels of the fixed_support_mask file which are different than 0."
    " Please note that the mask field of the fixed_support_mask file is totally irrelevant.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "initial_support",
    .display_name = "Initial Support",
    .variable_type = Type_Filename,
    .id = Id_Init_Support_Filename,
    .parent = &(variable_metadata[30]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.init_support_filename),
    .documentation = "The file name of the support that is used to start the reconstruction. If no file is given the"
    " initial support is derived from the autocorrelation.",
    .dependencies = NULL,
    .reserved = NULL  
  },
  {
    .variable_name = "support_intensity_threshold",
    .display_name = "Intensity Threshold",
    .variable_type = Type_Real,
    .id = Id_New_Level,
    .parent = &(variable_metadata[30]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.new_level),
    .documentation = "This setting only has any effect when used in conjunction with fixed support update. It's value is a fraction of the intensity of the most intense pixels."
    " During the calculation of the new support only pixels for which the normalized intensity (normalized to the most intense pixel) is greater than the support_intensity_threshold "
    " are kept in the support. For example for a support_intensity_threshold = 0.4 and for an image with the highest pixel intensity of 34000, all pixels above 13600 would be retained in the support.",
    .dependencies = depends_on_support_algorithm_with_threshold,
    .reserved = NULL
  },
  {
    .variable_name = "adapt_thres",
    .display_name = "Adaptative Threshold",
    .variable_type = Type_Bool,
    .id = Id_Adapt_Thres,
    .parent = &(variable_metadata[20]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|advanced,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.adapt_thres),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "blur",
    .display_name = "Blur",
    .variable_type = Type_Map_Real,
    .id = Id_Beta,
    .parent = &(variable_metadata[30]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.support_blur_evolution),
    .documentation = "Determines how much the image is blurred before the support is calculated from it. The value corresponds to 3 times the standard deviation of the gaussian kernel used to blur the image.",
    .dependencies =  NULL,
    .reserved = NULL
  },
  {
    .variable_name = "blur_radius_reduction_method",
    .display_name = "Blur Radius Reduction Method",
    .variable_type = Type_MultipleChoice,
    .id = Id_Blur_Radius_Reduction_Method,
    .parent = &(variable_metadata[30]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|advanced|deprecated,
    .list_valid_values = {GAUSSIAN_BLUR_REDUCTION,GEOMETRICAL_BLUR_REDUCTION,0},
    .list_valid_names = {"gaussian","geometrical",0},
    .variable_address = &(global_options.blur_radius_reduction_method),
    .documentation = "Specifies the function used for interpolation between the max and the minimum of the blur radius.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "minimum_blur_radius",
    .display_name = "Minimum Blur Radius",
    .variable_type = Type_Real,
    .id = Id_Min_Blur,
    .parent = &(variable_metadata[30]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|advanced|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.min_blur),
    .documentation = "During the support update procedure the real space image is blured with a gaussian. This gaussian starts with a radius of max_blur_radius and gradually decreases to"
    "minimum_blur_radius after iterations_to_min_blur iterations.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "RAAR_sigma",
    .display_name = "RAAR Sigma",
    .variable_type = Type_Real,
    .id = Id_Exp_Sigma,
    .parent = &(variable_metadata[20]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|advanced,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.exp_sigma),
    .documentation = "When using the RAAR algorithm the image amplitudes are allowed to deviate from input amplitudes by a fraction of their value. This fraction is given by the RAAR_sigma."
    " For example if RAAR_sigma is 0.05 then a pixel with an amplitude of 100 would be allowed to range between 95 and 105. The way the value is constrained is by using the so called modulus annulus projection."
    "For more information about the modulus annulus projection please see Pierre Thibault PhD thesis section 3.4.1.",
    .dependencies = depends_on_phasing_algorithm_is_raar,
    .reserved = NULL
  },
  {
    .variable_name = "dynamic_beta",
    .display_name = "Dynamic Beta",
    .variable_type = Type_Real,
    .id = Id_Dyn_Beta,
    .parent = &(variable_metadata[20]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|advanced|withSpecialValue|deprecated,
    .list_valid_values = {0,0},
    .list_valid_names = {"off",0},
    .variable_address = &(global_options.dyn_beta),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "initial_image",
    .display_name = "Initial Image",
    .variable_type = Type_Group,
    .id = Id_Initialization,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.dyn_beta),
    .documentation = "The group that contains the options relevant to the image used as starting point for the phasing.",
    .dependencies = NULL,
    .reserved = NULL
  },

  {
    .variable_name = "image_guess",
    .display_name = "Initial Realspace Image",
    .variable_type = Type_Filename,
    .id = Id_Image_Guess_Filename,
    .parent = &(variable_metadata[82]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.image_guess_filename),
    .documentation = "The file name of the real space starting image for the reconstruction. If no file is given the"
    " initial image is derived from the autocorrelation.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "random_initial_phases",
    .display_name = "Random Initial Phases",
    .variable_type = Type_Bool,
    .id = Id_Rand_Phases,
    .parent = &(variable_metadata[82]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.rand_phases),
    .documentation = "The initial image is created by taking the back fourier transform of the amplitudes using random phases",
    .dependencies = depends_on_initial_guess_from_autocorrelation,
    .reserved = NULL
  },
  {
    .variable_name = "random_initial_intensities",
    .display_name = "Random Initial Intensities",
    .variable_type = Type_Bool,
    .id = Id_Rand_Intensities,
    .parent = &(variable_metadata[82]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.rand_intensities),
    .documentation = "Each pixel of the initial image is replaced by a complex random number.",
    .dependencies = depends_on_initial_guess_from_autocorrelation,
    .reserved = NULL
  },

  {
    .variable_name = "support_real_error_threshold",
    .display_name = "Support Real Error Threshold",
    .variable_type = Type_Real,
    .id = Id_Real_Error_Threshold,
    .parent = &(variable_metadata[30]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|withSpecialValue,
    .list_valid_values = {-1,0},
    .list_valid_names = {"auto",0},
    .variable_address = &(global_options.real_error_threshold),
    .documentation = "The amount of real space error that the algorithm tries to achieve.",
    .dependencies = depends_on_support_algorithm_with_real_error_threshold,
    .reserved = NULL
  },
  {
    .variable_name = "error_reduction_iterations_after_loop",
    .display_name = "ER iterations after loop",
    .variable_type = Type_Int,
    .id = Id_Error_Reduction_Iterations_After_Loop,
    .parent = &(variable_metadata[20]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|advanced,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.error_reduction_iterations_after_loop),
    .documentation = "Number of Error Reduction iterations to be done in each outer loop iteration.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "enforce_positivity",
    .display_name = "Enforce Positivity",
    .variable_type = Type_Bool,
    .id = Id_Enforce_Positivity,
    .parent = &(variable_metadata[20]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|advanced,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.enforce_positivity),
    .documentation = "The real and imaginary parts of each pixel are replaced, respectively, by absolute value of the real and imaginary of the pixel at the end of each iteration.",
    .dependencies = depends_on_phasing_algorithm_with_positivity,
    .reserved = NULL
  },
  {
    .variable_name = "enforce_real",
    .display_name = "Enforce Real",
    .variable_type = Type_Bool,
    .id = Id_Enforce_Real,
    .parent = &(variable_metadata[20]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|advanced,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.enforce_real),
    .documentation = "Drop the imaginary part of the image at the end of each iteration",
    .dependencies = depends_on_phasing_algorithm_with_enforce_real,
    .reserved = NULL
  },
  {
    .variable_name = "charge_flip_sigma",
    .display_name = "Charge Flip Sigma",
    .variable_type = Type_Real,
    .id = Id_Charge_Flip_Sigma,
    .parent = &(variable_metadata[20]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.charge_flip_sigma),
    .documentation = "Value of the Sigma parameter used in the Charge Flipping algorithm",
    .dependencies = depends_on_phasing_algorithm_is_cflip,
    .reserved = NULL
  },
  {
    .variable_name = "real_image_file",
    .display_name = "Realspace Image File",
    .variable_type = Type_Filename,
    .id = Id_Real_Image_Filename,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.real_image_filename),
    .documentation = "The input h5 file that contains a real space image, that is then fourier transformed inside the program to calculate the diffraction amplitudes that are"
    "going to be used for phasing. Is is simply an alternative way to specify the diffraction amplitudes. Should not be used at the same time as amplitudes_file.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "rescale_initial_image",
    .display_name = "Rescale Initial Image",
    .variable_type = Type_Bool,
    .id = Id_Rescale_Amplitudes,
    .parent = &(variable_metadata[82]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|advanced,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.rescale_amplitudes),
    .documentation = "Rescales the image guess according to the input amplitudes, ensuring that it fullfills Parseval's theorem.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "remove_central_pixel_phase",
    .display_name = "Remove Central Pixel Phase",
    .variable_type = Type_Bool,
    .id = Id_Remove_Central_Pixel_phase,
    .parent = &(variable_metadata[20]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|advanced,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.remove_central_pixel_phase),
    .documentation = "Replaces the central pixel of the image by its absolute value after each iteration",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "perturb_weak_reflections",
    .display_name = "Perturb Weak Reflections",
    .variable_type = Type_Real,
    .id = Id_Perturb_Weak_Reflections,
    .parent = &(variable_metadata[20]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|withSpecialValue,
    .list_valid_values = {0,0},
    .list_valid_names = {"No",0},
    .variable_address = &(global_options.perturb_weak_reflections),
    .documentation = "Use a random phase for the pixels with the weakest intensity. The percentage of pixels considered weak is given by the value of this variable.",
    .dependencies = depends_on_phasing_algorithm_with_perturb_reflections,
    .reserved = NULL
  },
  {
    .variable_name = "autocorrelation_algorithm",
    .display_name = "Autocorrelation Selection Algorithm",
    .variable_type = Type_MultipleChoice,
    .id = Id_Patterson_Level_Algorithm,
    .parent = &(variable_metadata[82]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {FIXED,CONSTANT_AREA,0},
    .list_valid_names = {"threshold","area",0},
    .variable_address = &(global_options.patterson_level_algorithm),
    .documentation = "Defines the algorithm that is used to determine the boundaries of the autocorrelation.",
    .dependencies = depends_on_initial_guess_from_autocorrelation,
    .reserved = NULL
  },
  {
    .variable_name = "object_area",
    .display_name = "Object Area",
    .variable_type = Type_Map_Real,
    .id = Id_Object_Area,
    .parent = &(variable_metadata[30]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.object_area_evolution),
    .documentation = "Maximum object area as a ratio to the total image area.",
    .dependencies = depends_on_support_algorithm_with_area,
    .reserved = NULL
  },
  {
    .variable_name = "square_mask",
    .display_name = "Square Mask",
    .variable_type = Type_Real,
    .id = Id_Square_Mask,
    .parent = &(variable_metadata[30]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|advanced|withSpecialValue,
    .list_valid_values = {0,0},
    .list_valid_names = {"off",0},
    .variable_address = &(global_options.square_mask),
    .documentation = "Add a rectange, centered on the image center, to the support. The sides of the rectangle are given by this option, and is given as a ratio to the image sides.", 
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "autocorrelation_blur_radius",
    .display_name = "Autocorrelation Blur Radius",
    .variable_type = Type_Real,
    .id = Id_Patterson_Blur_Radius,
    .parent = &(variable_metadata[82]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|withSpecialValue,
    .list_valid_values = {0,0},
    .list_valid_names = {"off",0},
    .variable_address = &(global_options.patterson_blur_radius),
    .documentation = "Size of the blurring function applied to the autocorrelation before applying the thresholding function.",
    .dependencies = depends_on_patterson_algorithm_constant_area,
    .reserved = NULL
  },
  {
    .variable_name = "real_error_tolerance",
    .display_name = "Real Error Tolerance",
    .variable_type = Type_Real,
    .id = Id_Real_Error_Tolerance,
    .parent = &(variable_metadata[20]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|advanced|withSpecialValue,
    .list_valid_values = {-1,0},
    .list_valid_names = {"off",0},
    .variable_address = &(global_options.real_error_tolerance),
    .documentation = "If the real space error drops below this value the reconstruction stops",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "image_blur_period",
    .display_name = "Image Blur Period",
    .variable_type = Type_Int,
    .id = Id_Image_Blur_Period,
    .parent = &(variable_metadata[20]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|advanced|withSpecialValue,
    .list_valid_values = {0,0},
    .list_valid_names = {"off",0},
    .variable_address = &(global_options.image_blur_period),
    .documentation = "Period in iterations for the application of the blurring to the real space image.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "image_blur_radius",
    .display_name = "Image Blur Radius",
    .variable_type = Type_Real,
    .id = Id_Image_Blur_Radius,
    .parent = &(variable_metadata[20]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|advanced,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.image_blur_radius),
    .documentation = "Amount of blurring applied to the real space image periodically.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "iterations_to_min_object_area",
    .display_name = "Iterations to Min. Area",
    .variable_type = Type_Int,
    .id = Id_Iterations_To_Min_Object_Area,
    .parent = &(variable_metadata[30]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.iterations_to_min_object_area),
    .documentation = "Number of iterations necessary to reduce the support to its minimum size",
    .dependencies = depends_on_support_algorithm_with_changing_area,
    .reserved = NULL
  },
  {
    .variable_name = "min_object_area",
    .display_name = "Minimum Area",
    .variable_type = Type_Real,
    .id = Id_Min_Object_Area,
    .parent = &(variable_metadata[30]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.min_object_area),
    .documentation = "Minimum support area as a ratio to the total image area.",
    .dependencies = depends_on_support_algorithm_with_changing_area,
    .reserved = NULL
  },
  {
    .variable_name = "logfile",
    .display_name = "Log File",
    .variable_type = Type_Filename,
    .id = Id_Log_File,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.log_file),
    .documentation = "Name of the file where all output statistics are going to written to. Warning: This file is overwritten if it already exists!",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "logfile",
    .display_name = "Log File",
    .variable_type = Type_Filename,
    .id = Id_Log_File,
    .parent = &(variable_metadata[16]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.log_file),
    .documentation = "Name of the file where all output statistics are going to written to. Warning: This file is overwritten if it already exists!",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "output_period",
    .display_name = "Images Output Period",
    .variable_type = Type_Int,
    .id = Id_Output_Period,
    .parent = &(variable_metadata[16]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.output_period),
    .documentation = "The number of iterations between writing images to files. For example a value of 100 means that the program will output images at step 0,99,199,etc...",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "log_output_period",
    .display_name = "Log Output Period",
    .variable_type = Type_Int,
    .id = Id_Log_Output_Period,
    .parent = &(variable_metadata[16]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.log_output_period),
    .documentation = "The number of iterations between writing statistics to the log file. For example a value of 20 means that the program will output images at step 0,19,39,etc...",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "output_precision",
    .display_name = "Output Precision in Bits",
    .variable_type = Type_MultipleChoice,
    .id = Id_Output_Precision,
    .parent = &(variable_metadata[16]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|advanced,
    .list_valid_values = {4,8,0},
    .list_valid_names = {"32","64",0},
    .variable_address = &(global_options.output_precision),
    .documentation = "Number of bits of precision used in the output files",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "phases_min_blur_radius",
    .display_name = "Phases Min. Blur Radius",
    .variable_type = Type_Real,
    .id = Id_Phases_Min_Blur_Radius,
    .parent = &(variable_metadata[20]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|advanced|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.phases_min_blur_radius),
    .documentation = "Minimum amount of blurring applied to the image phases.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "phases_max_blur_radius",
    .display_name = "Phases Max Blur Radius",
    .variable_type = Type_Real,
    .id = Id_Phases_Max_Blur_Radius,
    .parent = &(variable_metadata[20]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun|advanced|deprecated,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.phases_max_blur_radius),
    .documentation = "Maximum amount of blurring applied to the image phases.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "phases_blur",
    .display_name = "Phases Blur",
    .variable_type = Type_Map_Real,
    .id = Id_Iterations_To_Min_Phases_Blur,
    .parent = &(variable_metadata[20]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|advanced,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.phases_blur_evolution),
    .documentation = "During the support update iteration the real"
    " image phases are blurred by this amount",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "intensities_std_dev_file",
    .display_name = "Intensities Std. Dev. File",
    .variable_type = Type_Filename,
    .id = Id_Solution_File,
    .parent = &(variable_metadata[1]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.intensities_std_dev_filename),
    .documentation = "File with the standard deviations of the input intensities",
    .dependencies = depends_on_amplitudes_file,
    .reserved = NULL
  },
  {
    .variable_name = "autocorrelation_support_file",
    .display_name = "Autocorrelation Support File",
    .variable_type = Type_Filename,
    .id = Id_Autocorrelation_Support_File,
    .parent = &(variable_metadata[1]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.autocorrelation_support_filename),
    .documentation = "Estimated support of the autocorrelation of the input. This can then be used to estimate the noise of the input data.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "filter_intensities",
    .display_name = "Filter Intensities",
    .variable_type = Type_Bool,
    .id = Id_Filter_Intensities,
    .parent = &(variable_metadata[30]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|advanced,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.filter_intensities),
    .documentation = "If enabled the amplitudes are filtered using the autocorrelation of the support at each iteration.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "gamma1",
    .display_name = "Gamma 1",
    .variable_type = Type_Real,
    .id = Id_Gamma1,
    .parent = &(variable_metadata[20]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|withSpecialValue,
    .list_valid_values = {-10000,0},
    .list_valid_names = {"auto",0},
    .variable_address = &(global_options.gamma1),
    .documentation = "Gamma1 or Gamma_S parameter of the difference map algorithm.",
    .dependencies = depends_on_diff_map,
    .reserved = NULL
  },
  {
    .variable_name = "gamma2",
    .display_name = "Gamma 2",
    .variable_type = Type_Real,
    .id = Id_Gamma2,
    .parent = &(variable_metadata[20]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|withSpecialValue,
    .list_valid_values = {-10000,0},
    .list_valid_names = {"auto",0},
    .variable_address = &(global_options.gamma2),
    .documentation = "Gamma2 or Gamma_F parameter of the difference map algorithm.",
    .dependencies = depends_on_diff_map,
    .reserved = NULL
  },
  {
    .variable_name = "support_image_averaging",
    .display_name = "Support Image Averaging",
    .variable_type = Type_Int,
    .id = Id_Support_Image_Averaging,
    .parent = &(variable_metadata[30]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|withSpecialValue,
    .list_valid_values = {1,0},
    .list_valid_names = {"off",0},
    .variable_address = &(global_options.support_image_averaging),
    .documentation = "The number of real_out images used the calculation of the support. Each image comes from a different iteration and their are averaged together",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "amplitudes_file",
    .display_name = "Amplitudes File",
    .variable_type = Type_Filename,
    .id = Id_Diffraction_Filename,
    .parent = &(variable_metadata[1]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.diffraction_filename),
    .documentation = "The input h5 file that contains the experimental diffraction amplitudes (not the intensities), with the center determined and with the quadrants shifted.",
    .dependencies = depends_on_no_realspace_image_file,
    .reserved = NULL
  },
  {
    .variable_name = "autocorrelation_threshold",
    .display_name = "Autocorrelation Threshold",
    .variable_type = Type_Real,
    .id = Id_Init_Level,
    .parent = &(variable_metadata[82]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.init_level),
    .documentation = "Corresponds to a fraction of the maximum value of a pixel in the autocorrelation image."
    " After normalizing to the maximum value pixels which have a value higher than this fraction will be included in the support.",
    .dependencies = depends_on_patterson_algorithm_fixed,
    .reserved = NULL
  },
  {
    .variable_name = "real_image_file",
    .display_name = "Realspace Image File",
    .variable_type = Type_Filename,
    .id = Id_Real_Image_Filename,
    .parent = &(variable_metadata[1]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.real_image_filename),
    .documentation = "The input h5 file that contains a real space image, that is then fourier transformed inside the program to calculate the diffraction amplitudes that are"
    "going to be used for phasing. Is is simply an alternative way to specify the diffraction amplitudes. Should not be used at the same time as amplitudes_file.",
    .dependencies = depends_on_no_amplitudes_file,
    .reserved = NULL
  },
  {
    .variable_name = "algorithm",
    .display_name = "Phasing Algorithm",
    .variable_type = Type_MultipleChoice,
    .id = Id_Algorithm,
    .parent = &(variable_metadata[20]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {HIO,RAAR,HPR,CFLIP,SO2D,RAAR_PROJ,HIO_PROJ,DIFF_MAP,0},
    .list_valid_names = {"hio","raar","hpr","cflip","so2d","raar_proj", "hio_proj","diff_map",0},
    .variable_address = &(global_options.algorithm),
    .documentation = "The type of algorithm used during the phase retrieval. A few other options then depend on the type of algorithm chosen.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "algorithm",
    .display_name = "Phasing Algorithm",
    .variable_type = Type_MultipleChoice,
    .id = Id_Algorithm,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {HIO,RAAR,HPR,CFLIP,RAAR_CFLIP,HAAR,SO2D,RAAR_PROJ,HIO_PROJ,DIFF_MAP,0},
    .list_valid_names = {"hio","raar","hpr","cflip","raar_cflip","haar","so2d","raar_proj","hio_proj","diff_map",0},
    .variable_address = &(global_options.algorithm),
    .documentation = "The type of algorithm used during the phase retrieval. A few other options then depend on the type of algorithm chosen.",
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "support_update_algorithm",
    .display_name = "Support Update Algorithm",
    .variable_type = Type_MultipleChoice,
    .id = Id_Support_Update_Algorithm,
    .parent = &(variable_metadata[30]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {FIXED,STEPPED,REAL_ERROR_CAPPED,REAL_ERROR_ADAPTATIVE,DECREASING_AREA,COMPLEX_DECREASING_AREA,0},
    .list_valid_names = {"threshold","stepped","real_error_capped","real_error_adaptative","decreasing_area","complex_decreasing_area",0},
    .variable_address = &(global_options.support_update_algorithm),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "support_update_algorithm",
    .display_name = "Support Update Algorithm",
    .variable_type = Type_MultipleChoice,
    .id = Id_Support_Update_Algorithm,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun|deprecated,
    .list_valid_values = {FIXED,STEPPED,REAL_ERROR_CAPPED,REAL_ERROR_ADAPTATIVE,CONSTANT_AREA,DECREASING_AREA,COMPLEX_DECREASING_AREA,0},
    .list_valid_names = {"fixed","stepped","real_error_capped","real_error_adaptative","constant_area","decreasing_area","complex_decreasing_area",0},
    .variable_address = &(global_options.support_update_algorithm),
    .dependencies = NULL,
    .reserved = NULL
  },
  {
    .variable_name = "autocorrelation_area",
    .display_name = "Autocorrelation Area",
    .variable_type = Type_Real,
    .id = Id_Autocorrelation_Area,
    .parent = &(variable_metadata[82]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.autocorrelation_area),
    .documentation = "Maximum autocorrelation area as a ratio to the total image area.",
    .dependencies = depends_on_patterson_algorithm_constant_area,
    .reserved = NULL
  },
  {
    .variable_name = "beta",
    .display_name = "Beta",
    .variable_type = Type_Map_Real,
    .id = Id_Beta,
    .parent = &(variable_metadata[20]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.beta_evolution),
    .documentation = "Relaxation parameter used in several algorithms. Please refer to the specific algorithm documentation for more information.",
    .dependencies =  depends_on_phasing_algorithm_with_beta,
    .reserved = NULL
  },
    {
    .variable_name = "innerloop_iterations",
    .display_name = "Innerloop Iterations",
    .variable_type = Type_Int,
    .id = Id_Iterations,
    .parent = &(variable_metadata[30]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.iterations),
    .documentation = "Number of iterations of the phasing basic algorithm which are performed in between the support update steps.",
    .dependencies = NULL,
    .reserved = NULL
  }


};


/* Don't forget to update this one!! */
const int number_of_global_options = 131;


int get_list_value_from_list_name(VariableMetadata * md,char * name){
  int i = 0;
  unsigned int j = 0;
  char buffer[1024];
  strcpy(buffer,name);
  for(j=0;j<strlen(buffer);j++){
    buffer[j] = tolower(buffer[j]);
  }

  while(md->list_valid_names[i]){
    if(strcmp(md->list_valid_names[i],name) == 0){
      return md->list_valid_values[i];
    }
    i++;
  }
  return -1;
}
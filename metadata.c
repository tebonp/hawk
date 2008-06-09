#include "configuration.h"



VariableMetadata variable_metadata[100] = {
  {
    .variable_name = "ROOT",
    .variable_type = Type_Group,
    .id = Id_Root,
    .parent = NULL,
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.diffraction_filename),
    .documentation = "The base group",
    .reserved = NULL
  },
  {
    .variable_name = "amplitudes_file",
    .variable_type = Type_String,
    .id = Id_Diffraction_Filename,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.diffraction_filename),
    .documentation = "The input h5 file that contains the experimental diffraction amplitudes (not the intensities), with the center determined and with the quadrants shifted.",
    .reserved = NULL
  },
  {
    .variable_name = "real_image_file",
    .variable_type = Type_String,
    .id = Id_Real_Image_Filename,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.real_image_filename),
    .documentation = "The input h5 file that contains a real space image, that is then fourier transformed inside the program to calculate the diffraction amplitudes that are"
    "going to be used for phasing. Is is simply an alternative way to specify the diffraction amplitudes. Should not be used at the same time as amplitudes_file.",
    .reserved = NULL
  },
  {
    .variable_name = "max_blur_radius",
    .variable_type = Type_Real,
    .id = Id_Max_Blur_Radius,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.max_blur_radius),
    .documentation = "Correponds to 3 times the maximum standard deviation of the gaussian blur applied before doing any further processing to the real space image guess."
    " The real space image guess is then passed on to the rest of the computing chain that calculates the new support."
    " This option only affects the support calculation routines."
    " Typically there is a maximum and a minimum blur radius which the program smoothly interpolates in between during the first iterations_to_min_blur iterations",
    .reserved = NULL
  },
  {
    .variable_name = "patterson_threshold",
    .variable_type = Type_Real,
    .id = Id_Init_Level,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.init_level),
    .documentation = "Corresponds to a fraction of the maximum value of a pixel in the autocorrelation image."
    " After normalizing to the maximum value pixels which have a value higher than this fraction will be included in the support.",
    .reserved = NULL
  },
  {
    .variable_name = "beta",
    .variable_type = Type_Real,
    .id = Id_Beta,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.beta),
    .documentation = "Relaxation parameter used in several algorithms. Please refer to the specific algorithm documentation for more information.",
    .reserved = NULL
  },
  {
    .variable_name = "innerloop_iterations",
    .variable_type = Type_Int,
    .id = Id_Iterations,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.iterations),
    .documentation = "Number of iterations of the phasing basic algorithm which are performed in between the support update steps.",
    .reserved = NULL
  },
  {
    .variable_name = "fixed_support_mask",
    .variable_type = Type_String,
    .id = Id_Support_Mask_Filename,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.support_mask_filename),
    .documentation = "The name of an .h5 file which defines a mask that will be added to the support after every support update."
    " The pixels of the image file with a value different than 0 will be added to the support. "
    " The new support will then be the union of the original support with the pixels of the fixed_support_mask file which are different than 0."
    " Please note that the mask field of the fixed_support_mask file is totally irrelevant.",
    .reserved = NULL
  },
  {
    .variable_name = "initial_support",
    .variable_type = Type_String,
    .id = Id_Init_Support_Filename,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.init_support_filename),
    .documentation = "The file name of the support that is used to start the reconstruction. If no file is given the"
    " initial support is derived from the autocorrelation.",
    .reserved = NULL  
  },
  {
    .variable_name = "image_guess",
    .variable_type = Type_String,
    .id = Id_Image_Guess_Filename,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.image_guess_filename),
    .documentation = "The file name of the real space starting image for the reconstruction. If no file is given the"
    " initial image is derived from the autocorrelation.",
    .reserved = NULL
  },
  {
    .variable_name = "added_noise",
    .variable_type = Type_Real,
    .id = Id_Noise,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.noise),
    .documentation = "Obsolete option",
    .reserved = NULL
  },
  {
    .variable_name = "beamstop_radius",
    .variable_type = Type_Real,
    .id = Id_Beamstop,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.beamstop),
    .documentation = "Obsolete option",
    .reserved = NULL
  },
  {
    .variable_name = "support_intensity_threshold",
    .variable_type = Type_Real,
    .id = Id_New_Level,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.new_level),
    .documentation = "This setting only has any effect when used in conjunction with fixed support update. It's value is a fraction of the intensity of the most intense pixels."
    " During the calculation of the new support only pixels for which the normalized intensity (normalized to the most intense pixel) is greater than the support_intensity_threshold "
    " are kept in the support. For example for a support_intensity_threshold = 0.4 and for an image with the highest pixel intensity of 34000, all pixels above 13600 would be retained in the support.",
    .reserved = NULL
  },
  {
    .variable_name = "iterations_to_min_blur",
    .variable_type = Type_Int,
    .id = Id_Iterations_To_Min_Blur,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.iterations_to_min_blur),
    .documentation = "During the support update procedure the real space image is blured with a gaussian. This gaussian starts with a radius of max_blur_radius and gradually decreases to"
    "minimum_blur_radius after iterations_to_min_blur iterations.",
    .reserved = NULL
  },
  {
    .variable_name = "blur_radius_reduction_method",
    .variable_type = Type_MultipleChoice,
    .id = Id_Blur_Radius_Reduction_Method,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {GAUSSIAN_BLUR_REDUCTION,GEOMETRICAL_BLUR_REDUCTION,0},
    .list_valid_names = {"gaussian","geometrical",0},
    .variable_address = &(global_options.blur_radius_reduction_method),
    .documentation = "Specifies the function used for interpolation between the max and the minimum of the blur radius.",
    .reserved = NULL
  },
  {
    .variable_name = "minimum_blur_radius",
    .variable_type = Type_Real,
    .id = Id_Min_Blur,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.min_blur),
    .documentation = "During the support update procedure the real space image is blured with a gaussian. This gaussian starts with a radius of max_blur_radius and gradually decreases to"
    "minimum_blur_radius after iterations_to_min_blur iterations.",
    .reserved = NULL
  },
  {
    .variable_name = "logfile",
    .variable_type = Type_String,
    .id = Id_Log_File,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.log_file),
    .documentation = "Name of the file where all output statistics are going to written to. Warning: This file is overwritten if it already exists!",
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
    .reserved = NULL
  },
  {
    .variable_name = "output_period",
    .variable_type = Type_Int,
    .id = Id_Output_Period,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.output_period),
    .documentation = "The number of iterations between writing images to files. For example a value of 100 means that the program will output images at step 0,99,199,etc...",
    .reserved = NULL
  },
  {
    .variable_name = "log_output_period",
    .variable_type = Type_Int,
    .id = Id_Log_Output_Period,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.log_output_period),
    .documentation = "The number of iterations between writing statistics to the log file. For example a value of 20 means that the program will output images at step 0,19,39,etc...",
    .reserved = NULL
  },
  {
    .variable_name = "algorithm",
    .variable_type = Type_MultipleChoice,
    .id = Id_Algorithm,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {HIO,RAAR,HPR,CFLIP,RAAR_CFLIP,HAAR,SO2D,RAAR_PROJ,0},
    .list_valid_names = {"hio","raar","hpr","cflip","raar_cflip","haar","so2d","raar_proj",0},
    .variable_address = &(global_options.algorithm),
    .documentation = "The type of algorithm used during the phase retrieval. A few other options then depend on the type of algorithm chosen.",
    .reserved = NULL
  },
  {
    .variable_name = "RAAR_sigma",
    .variable_type = Type_Real,
    .id = Id_Exp_Sigma,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.exp_sigma),
    .documentation = "When using the RAAR algorithm the image amplitudes are allowed to deviate from input amplitudes by a fraction of their value. This fraction is given by the RAAR_sigma."
    " For example if RAAR_sigma is 0.05 then a pixel with an amplitude of 100 would be allowed to range between 95 and 105. The way the value is constrained is by using the so called modulus annulus projection."
    "For more information about the modulus annulus projection please see Pierre Thibault PhD thesis section 3.4.1.",
    .reserved = NULL
  },
  {
    .variable_name = "dynamic_beta",
    .variable_type = Type_Real,
    .id = Id_Dyn_Beta,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.dyn_beta),
    .reserved = NULL
  },
  {
    .variable_name = "random_initial_phases",
    .variable_type = Type_Bool,
    .id = Id_Rand_Phases,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.rand_phases),
    .reserved = NULL
  },
  {
    .variable_name = "random_initial_intensities",
    .variable_type = Type_Bool,
    .id = Id_Rand_Intensities,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.rand_intensities),
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
    .reserved = NULL
  },
  {
    .variable_name = "adapt_thres",
    .variable_type = Type_Bool,
    .id = Id_Adapt_Thres,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.adapt_thres),
    .reserved = NULL
  },
  {
    .variable_name = "automatic",
    .variable_type = Type_Bool,
    .id = Id_Automatic,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.dyn_beta),
    .reserved = NULL
  },
  {
    .variable_name = "work_directory",
    .variable_type = Type_String,
    .id = Id_Work_Dir,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.work_dir),
    .reserved = NULL
  },
  {
    .variable_name = "support_real_error_threshold",
    .variable_type = Type_Real,
    .id = Id_Real_Error_Threshold,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.real_error_threshold),
    .reserved = NULL
  },
  {
    .variable_name = "support_update_algorithm",
    .variable_type = Type_MultipleChoice,
    .id = Id_Support_Update_Algorithm,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {FIXED,STEPPED,REAL_ERROR_CAPPED,REAL_ERROR_ADAPTATIVE,CONSTANT_AREA,DECREASING_AREA,0},
    .list_valid_names = {"fixed","stepped","real_error_capped","real_error_adaptative","constant_area","decreasing_area",0},
    .variable_address = &(global_options.support_update_algorithm),
    .reserved = NULL
  },
  {
    .variable_name = "output_precision",
    .variable_type = Type_Int,
    .id = Id_Output_Precision,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.output_precision),
    .reserved = NULL
  },
  {
    .variable_name = "error_reduction_iterations_after_loop",
    .variable_type = Type_Int,
    .id = Id_Error_Reduction_Iterations_After_Loop,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.error_reduction_iterations_after_loop),
    .reserved = NULL
  },
  {
    .variable_name = "enforce_positivity",
    .variable_type = Type_Real,
    .id = Id_Enforce_Positivity,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.enforce_positivity),
    .reserved = NULL
  },
  {
    .variable_name = "enforce_real",
    .variable_type = Type_Int,
    .id = Id_Enforce_Real,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.enforce_real),
    .reserved = NULL
  },
  {
    .variable_name = "genetic_optimization",
    .variable_type = Type_Bool,
    .id = Id_Genetic_Optimization,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.genetic_optimization),
    .reserved = NULL
  },
  {
    .variable_name = "charge_flip_sigma",
    .variable_type = Type_Real,
    .id = Id_Charge_Flip_Sigma,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.charge_flip_sigma),
    .reserved = NULL
  },
  {
    .variable_name = "rescale_amplitudes",
    .variable_type = Type_Bool,
    .id = Id_Rescale_Amplitudes,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.rescale_amplitudes),
    .reserved = NULL
  },
  {
    .variable_name = "square_mask",
    .variable_type = Type_Real,
    .id = Id_Square_Mask,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.square_mask),
    .reserved = NULL
  },
  {
    .variable_name = "patterson_blur_radius",
    .variable_type = Type_Real,
    .id = Id_Patterson_Blur_Radius,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.patterson_blur_radius),
    .reserved = NULL
  },
  {
    .variable_name = "remove_central_pixel_phase",
    .variable_type = Type_Bool,
    .id = Id_Remove_Central_Pixel_phase,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.remove_central_pixel_phase),
    .reserved = NULL
  },
  {
    .variable_name = "perturb_weak_reflections",
    .variable_type = Type_Real,
    .id = Id_Perturb_Weak_Reflections,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.perturb_weak_reflections),
    .reserved = NULL
  },
  {
    .variable_name = "nthreads",
    .variable_type = Type_Int,
    .id = Id_Nthreads,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.nthreads),
    .reserved = NULL
  },
  {
    .variable_name = "break_centrosym_period",
    .variable_type = Type_Int,
    .id = Id_Break_Centrosym_Period,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.break_centrosym_period),
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
    .reserved = NULL
  },
  {
    .variable_name = "real_error_tolerance",
    .variable_type = Type_Real,
    .id = Id_Real_Error_Tolerance,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.real_error_tolerance),
    .reserved = NULL
  },
  {
    .variable_name = "max_iterations",
    .variable_type = Type_Int,
    .id = Id_Max_Iterations,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.max_iterations),
    .reserved = NULL
  },
  {
    .variable_name = "patterson_level_algorithm",
    .variable_type = Type_MultipleChoice,
    .id = Id_Patterson_Level_Algorithm,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {FIXED,STEPPED,REAL_ERROR_CAPPED,REAL_ERROR_ADAPTATIVE,CONSTANT_AREA,DECREASING_AREA,0},
    .list_valid_names = {"fixed","stepped","real_error_capped","real_error_adaptative","constant_area","decreasing_area",0},
    .variable_address = &(global_options.patterson_level_algorithm),
    .reserved = NULL
  },
  {
    .variable_name = "object_area",
    .variable_type = Type_Real,
    .id = Id_Object_Area,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.object_area),
    .reserved = NULL
  },
  {
    .variable_name = "image_blur_period",
    .variable_type = Type_Int,
    .id = Id_Image_Blur_Period,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.image_blur_period),
    .reserved = NULL
  },
  {
    .variable_name = "image_blur_radius",
    .variable_type = Type_Real,
    .id = Id_Image_Blur_Radius,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.image_blur_radius),
    .reserved = NULL
  },
  {
    .variable_name = "iterations_to_min_object_area",
    .variable_type = Type_Int,
    .id = Id_Iterations_To_Min_Object_Area,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.iterations_to_min_object_area),
    .reserved = NULL
  },
  {
    .variable_name = "min_object_area",
    .variable_type = Type_Real,
    .id = Id_Min_Object_Area,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.min_object_area),
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
    .reserved = NULL
  },
  {
    .variable_name = "solution_file",
    .variable_type = Type_String,
    .id = Id_Solution_File,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isSettableDuringRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.solution_filename),
    .reserved = NULL
  },
  {
    .variable_name = "phases_min_blur_radius",
    .variable_type = Type_Real,
    .id = Id_Phases_Min_Blur_Radius,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.phases_min_blur_radius),
    .reserved = NULL
  },
  {
    .variable_name = "phases_max_blur_radius",
    .variable_type = Type_Real,
    .id = Id_Phases_Max_Blur_Radius,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.phases_max_blur_radius),
    .reserved = NULL
  },
  {
    .variable_name = "iterations_to_min_phases_blur",
    .variable_type = Type_Int,
    .id = Id_Iterations_To_Min_Phases_Blur,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.iterations_to_min_phases_blur),
    .reserved = NULL
  },
  {
    .variable_name = "intensities_std_dev_file",
    .variable_type = Type_String,
    .id = Id_Solution_File,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.intensities_std_dev_filename),
    .reserved = NULL
  },
  {
    .variable_name = "autocorrelation_support_file",
    .variable_type = Type_String,
    .id = Id_Autocorrelation_Support_File,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isGettableBeforeRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.autocorrelation_support_filename),
    .reserved = NULL
  },
  {
    .variable_name = "filter_intensities",
    .variable_type = Type_Bool,
    .id = Id_Filter_Intensities,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.filter_intensities),
    .reserved = NULL
  },
  {
    .variable_name = "object_area_checkpoints",
    .variable_type = Type_Vector_Int,
    .id = Id_Object_Area_Checkpoints,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.object_area_checkpoints),
    .reserved = NULL
  },
  {
    .variable_name = "object_area_at_checkpoints",
    .variable_type = Type_Vector_Real,
    .id = Id_Object_Area_at_Checkpoints,
    .parent = &(variable_metadata[0]),
    .variable_properties = isSettableBeforeRun|isSettableDuringRun|isGettableBeforeRun|isGettableDuringRun,
    .list_valid_values = {0},
    .list_valid_names = {0},
    .variable_address = &(global_options.object_area_at_checkpoints),
    .reserved = NULL
  }
};


/* Don't forget to update this one!! */
const int number_of_global_options = 64;
